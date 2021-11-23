/*
 * Copyright (c) 2015, Devan Lai
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

#ifndef BACKUP_H_INCLUDED
#define BACKUP_H_INCLUDED

enum BackupRegister {
    BKP0 = 0,
    BKP1,
    BKP2,
    BKP3,
    BKP4
};

extern void backup_write(enum BackupRegister reg, uint32_t value);
extern uint32_t backup_read(enum BackupRegister reg);

enum ResetSource {
    RST_SRC_LPWR,
    RST_SRC_WWDG,
    RST_SRC_IWDG,
    RST_SRC_SW,
    RST_SRC_POR,
    RST_SRC_PIN
};

extern bool backup_check_reset_source(enum ResetSource src);
extern void backup_clear_reset_source(void);

#endif
