#!/usr/bin/env python3
"""Flush DevNonces on ChirpStack v4 via REST API."""
import os
import sys
try:
    import requests
except ImportError:
    print("ERROR: 'requests' module not found. Install with: pip3 install requests")
    sys.exit(1)

HOST = os.environ.get("CHIRPSTACK_HOST", "http://chirpstack.example.com:8090")
API_KEY = os.environ.get("CHIRPSTACK_API_KEY", "YOUR_CHIRPSTACK_API_KEY")
DEV_EUI = os.environ.get("DEV_EUI", "0011223344556677")

headers = {"Grpc-Metadata-Authorization": "Bearer " + API_KEY}

print(f"Flushing DevNonces for {DEV_EUI} on {HOST}...")

r = requests.delete(
    f"{HOST}/api/devices/{DEV_EUI}/dev-nonces",
    headers=headers,
    timeout=5,
)

if r.status_code == 200:
    print("DevNonces flushed successfully!")
else:
    print(f"Failed (HTTP {r.status_code}): {r.text}")
    sys.exit(1)
