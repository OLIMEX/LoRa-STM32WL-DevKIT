/*
 * Copyright (c) 2016, Devan Lai
 *
 * Permission to use, copy, modify, and/or distribute this software
 * for any purpose with or without fee is hereby granted, provided
 * that the above copyright notice and this permission notice
 * appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL
 * WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE
 * AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
 * LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#include <libopencm3/usb/usbd.h>
#include <libopencm3/usb/cdc.h>
#include "composite_usb_conf.h"
#include "vcdc.h"
#include "config.h"

#if VCDC_AVAILABLE

/* Descriptor structures */
const struct cdc_acm_functional_descriptors vcdc_acm_functional_descriptors = {
    .header = {
        .bFunctionLength = sizeof(struct usb_cdc_header_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_HEADER,
        .bcdCDC = 0x0110,
    },
    .call_mgmt = {
        .bFunctionLength =
        sizeof(struct usb_cdc_call_management_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_CALL_MANAGEMENT,
        .bmCapabilities = 0,
        .bDataInterface = INTF_VCDC_DATA,
    },
    .acm = {
        .bFunctionLength = sizeof(struct usb_cdc_acm_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_ACM,
        .bmCapabilities = 0,
    },
    .cdc_union = {
        .bFunctionLength = sizeof(struct usb_cdc_union_descriptor),
        .bDescriptorType = CS_INTERFACE,
        .bDescriptorSubtype = USB_CDC_TYPE_UNION,
        .bControlInterface = INTF_VCDC_COMM,
        .bSubordinateInterface0 = INTF_VCDC_DATA,
    }
};

/* Input/output buffers */
static uint8_t vcdc_tx_buffer[VCDC_TX_BUFFER_SIZE];
static uint8_t vcdc_rx_buffer[VCDC_RX_BUFFER_SIZE];

static uint16_t vcdc_tx_head = 0;
static uint16_t vcdc_tx_tail = 0;

static uint16_t vcdc_rx_head = 0;
static uint16_t vcdc_rx_tail = 0;

_Static_assert((VCDC_RX_BUFFER_SIZE >= USB_VCDC_MAX_PACKET_SIZE),
               "RX buffer too small");

#define IS_POW_OF_TWO(X) (((X) & ((X)-1)) == 0)
_Static_assert(IS_POW_OF_TWO(VCDC_RX_BUFFER_SIZE),
               "Unmasked circular buffer size must be a power of two");
_Static_assert(IS_POW_OF_TWO(VCDC_TX_BUFFER_SIZE),
               "Unmasked circular buffer size must be a power of two");
_Static_assert(VCDC_TX_BUFFER_SIZE <= UINT16_MAX/2,
               "Buffer size too big for unmasked circular buffer");
_Static_assert(VCDC_RX_BUFFER_SIZE <= UINT16_MAX/2,
               "Buffer size too big for unmasked circular buffer");

static bool vcdc_tx_buffer_empty(void) {
    return vcdc_tx_head == vcdc_tx_tail;
}

static bool vcdc_tx_buffer_full(void) {
    return (uint16_t)(vcdc_tx_tail - vcdc_tx_head) == VCDC_TX_BUFFER_SIZE;
}

static void vcdc_tx_buffer_put(uint8_t data) {
    vcdc_tx_buffer[vcdc_tx_tail % VCDC_TX_BUFFER_SIZE] = data;
    vcdc_tx_tail++;
}

static uint8_t vcdc_tx_buffer_get(void) {
    uint8_t data = vcdc_tx_buffer[vcdc_tx_head % VCDC_TX_BUFFER_SIZE];
    vcdc_tx_head++;
    return data;
}

static bool vcdc_rx_buffer_empty(void) {
    return vcdc_rx_head == vcdc_rx_tail;
}

static bool vcdc_rx_buffer_full(void) {
    return (uint16_t)(vcdc_rx_tail - vcdc_rx_head) == VCDC_RX_BUFFER_SIZE;
}

static void vcdc_rx_buffer_put(uint8_t data) {
    vcdc_rx_buffer[vcdc_rx_tail % VCDC_RX_BUFFER_SIZE] = data;
    vcdc_rx_tail++;
}

static uint8_t vcdc_rx_buffer_get(void) {
    uint8_t data = vcdc_rx_buffer[vcdc_rx_head % VCDC_RX_BUFFER_SIZE];
    vcdc_rx_head++;
    return data;
}

size_t vcdc_recv_buffered(uint8_t* data, size_t max_bytes) {
    size_t bytes_read = 0;
    while (!vcdc_rx_buffer_empty() && (bytes_read < max_bytes)) {
        data[bytes_read++] = vcdc_rx_buffer_get();
    }

    return bytes_read;
}

size_t vcdc_send_buffered(const uint8_t* data, size_t num_bytes) {
    size_t bytes_queued = 0;
    while (!vcdc_tx_buffer_full() && bytes_queued < num_bytes) {
        vcdc_tx_buffer_put(data[bytes_queued++]);
    }

    return bytes_queued;
}

size_t vcdc_send_buffer_space(void) {
    return VCDC_TX_BUFFER_SIZE - (uint16_t)(vcdc_tx_tail - vcdc_tx_head);
}

/* User callbacks */
static GenericCallback vcdc_rx_callback = NULL;
static GenericCallback vcdc_tx_callback = NULL;

static enum usbd_request_return_codes
vcdc_control_class_request(usbd_device *usbd_dev,
                           struct usb_setup_data *req,
                           uint8_t **buf, uint16_t *len,
                           usbd_control_complete_callback* complete) {
    (void)complete;
    (void)usbd_dev;
    (void)buf;
    (void)len;

    if (req->wIndex != INTF_VCDC_DATA && req->wIndex != INTF_VCDC_COMM) {
        return USBD_REQ_NEXT_CALLBACK;
    }
    enum usbd_request_return_codes status = USBD_REQ_NOTSUPP;

    switch (req->bRequest) {
        case USB_CDC_REQ_SET_CONTROL_LINE_STATE: {
            /*
             * This Linux cdc_acm driver requires this to be implemented
             * even though it's optional in the CDC spec, and we don't
             * advertise it in the ACM functional descriptor.
             */

            status = USBD_REQ_HANDLED;
            break;
        }
        case USB_CDC_REQ_SET_LINE_CODING: {
            /* Accept whatever is requested */
            status = USBD_REQ_HANDLED;
            break;
        }
        case USB_CDC_REQ_GET_LINE_CODING: {
            /* Send back a dummy default coding */
            struct usb_cdc_line_coding *coding;
            coding = (struct usb_cdc_line_coding*)(*buf);
            coding->dwDTERate = DEFAULT_BAUDRATE;
            coding->bCharFormat = USB_CDC_1_STOP_BITS;
            coding->bParityType = USB_CDC_NO_PARITY;
            coding->bDataBits = 8;
            *len = sizeof(struct usb_cdc_line_coding);
            status = USBD_REQ_HANDLED;
            break;
        }
        default: {
            status = USBD_REQ_NOTSUPP;
            break;
        }
    }

    return status;
}

/* Receive data from the host */
static void vcdc_bulk_data_out(usbd_device *usbd_dev, uint8_t ep) {
    uint8_t buf[USB_VCDC_MAX_PACKET_SIZE];
    uint16_t len = usbd_ep_read_packet(usbd_dev, ep, (void*)buf, sizeof(buf));

    uint16_t i;
    for (i=0; i < len && !vcdc_rx_buffer_full(); i++) {
        vcdc_rx_buffer_put(buf[i]);
    }
    
    if (len > 0 && (vcdc_rx_callback != NULL)) {
        vcdc_rx_callback();
    }
}

static void vcdc_set_config(usbd_device *usbd_dev, uint16_t wValue) {
    (void)wValue;

    usbd_ep_setup(usbd_dev, ENDP_VCDC_DATA_OUT, USB_ENDPOINT_ATTR_BULK, 64,
                  vcdc_bulk_data_out);
    usbd_ep_setup(usbd_dev, ENDP_VCDC_DATA_IN, USB_ENDPOINT_ATTR_BULK, 64,
                  NULL);
    usbd_ep_setup(usbd_dev, ENDP_VCDC_COMM_IN, USB_ENDPOINT_ATTR_INTERRUPT, 16, NULL);

    cmp_usb_register_control_class_callback(INTF_VCDC_DATA, vcdc_control_class_request);
    cmp_usb_register_control_class_callback(INTF_VCDC_COMM, vcdc_control_class_request);
}

static uint16_t packet_len = 0;
static uint8_t packet_buffer[USB_VCDC_MAX_PACKET_SIZE];

static void vcdc_app_reset(void) {
    packet_len = 0;
}

static usbd_device* vcdc_usbd_dev;

void vcdc_app_setup(usbd_device* usbd_dev,
                    GenericCallback vcdc_tx_cb,
                    GenericCallback vcdc_rx_cb) {
    vcdc_usbd_dev = usbd_dev;
    vcdc_tx_callback = vcdc_tx_cb;
    vcdc_rx_callback = vcdc_rx_cb;

    cmp_usb_register_set_config_callback(vcdc_set_config);
    cmp_usb_register_reset_callback(vcdc_app_reset);
}

bool vcdc_app_update(void) {
    bool active = false;

    while (packet_len < USB_VCDC_MAX_PACKET_SIZE && !vcdc_tx_buffer_empty()) {
        packet_buffer[packet_len] = vcdc_tx_buffer_get();
        packet_len++;
    }

    if (packet_len > 0 && cmp_usb_configured()) {
        uint16_t sent = usbd_ep_write_packet(vcdc_usbd_dev, ENDP_VCDC_DATA_IN,
                                             (const void*)packet_buffer,
                                             packet_len);
        
        if (sent != 0) {
            packet_len = 0;
            active = true;
            if (vcdc_tx_callback != NULL) {
                vcdc_tx_callback();
            }
        }
    }
    
    return active;
}

void vcdc_putchar(const char c) {
    if (!vcdc_tx_buffer_full()) {
        vcdc_tx_buffer_put(c);
    }
}

void vcdc_print(const char* s) {
    while (*s != '\0') {
        vcdc_putchar(*s++);
    }
}

void vcdc_println(const char* s) {
    while (*s != '\0') {
        vcdc_putchar(*s++);
    }
    vcdc_putchar('\r');
    vcdc_putchar('\n');
}

void vcdc_print_hex_nibble(uint8_t x) {
    uint8_t nibble = x & 0x0F;
    char nibble_char;
    if (nibble < 10) {
        nibble_char = '0' + nibble;
    } else {
        nibble_char = 'A' + (nibble - 10);
    }
    vcdc_putchar(nibble_char);
}

void vcdc_print_hex_byte(uint8_t x) {
    vcdc_print_hex_nibble(x >> 4);
    vcdc_print_hex_nibble(x);
}

void vcdc_print_hex(uint32_t x) {
    vcdc_print_hex_nibble((uint8_t)(x >> 28));
    vcdc_print_hex_nibble((uint8_t)(x >> 24));
    vcdc_print_hex_nibble((uint8_t)(x >> 20));
    vcdc_print_hex_nibble((uint8_t)(x >> 16));
    vcdc_print_hex_nibble((uint8_t)(x >> 12));
    vcdc_print_hex_nibble((uint8_t)(x >> 8));
    vcdc_print_hex_nibble((uint8_t)(x >> 4));
    vcdc_print_hex_nibble((uint8_t)(x >> 0));
}

#endif
