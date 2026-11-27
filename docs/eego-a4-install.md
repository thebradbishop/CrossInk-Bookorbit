---
title: Installing on the EEGO Reader A4
---

# Installing on the EEGO Reader A4

> [!WARNING]
> **Use at your own risk.** This is unofficial, community-built firmware. It is not made,
> endorsed or supported by EEGO/EEGOREAD, the CrossPoint, CrossInk or CrossInk-Bookorbit
> projects, or BookOrbit. It has been tested on very few devices.
>
> - Flashing replaces the reader's stock firmware. **There is no "undo" button**: the only
>   way back is a backup you made yourself (step 2 below).
> - Flashing custom firmware may void your warranty.
> - Something can go wrong: a failed flash, a reader that will not start, lost settings or
>   reading progress. You are responsible for your device and your data.
> - It is provided as is, without warranty of any kind (see [LICENSE](../LICENSE)).
>
> If any of that is not acceptable to you, do not flash it.

This firmware is [CrossInk](https://github.com/uxjulia/CrossInk) with
[BookOrbit](https://github.com/bookorbit/bookorbit) integration, from
[CrossInk-Bookorbit](https://github.com/agosez/CrossInk-Bookorbit), plus the additions listed
in the [changelog](../CHANGELOG.md). It runs on the EEGO Reader A4 and A4 Lite (ESP32-S3,
768 × 552 screen).

## What you need

- The reader, charged, and a **USB-C cable that carries data** (not a charge-only cable).
- A computer with Python 3 (macOS, Linux or Windows).
- The four files from the [latest release](https://github.com/thebradbishop/CrossInk-Bookorbit/releases):
  `firmware-eego_a4.bin`, `bootloader.bin`, `partitions.bin` and `boot_app0.bin`. Put them
  in one folder.

## 1. Install the flashing tool

```bash
python3 -m pip install esptool
```

On Windows, use `py` instead of `python3` in every command on this page.

## 2. Back up the stock firmware (strongly recommended)

Connect the reader. If it appears as a USB drive (often called NO NAME), eject it first.
Then, in the folder where you want the backup:

```bash
python3 -m esptool --chip esp32s3 read_flash 0 0x1000000 eego-a4-stock-16MB.bin
```

This copies the reader's whole 16 MB of flash and takes a few minutes. Keep the file
somewhere safe: it is your only way back to the stock firmware.

## 3. Flash

From the folder that holds the four files:

```bash
python3 -m esptool --chip esp32s3 --baud 921600 write_flash --flash_mode dio --flash_size 16MB 0x0 bootloader.bin 0x8000 partitions.bin 0xe000 boot_app0.bin 0x10000 firmware-eego_a4.bin
```

It ends with `Hard resetting via RTS pin...` and the reader restarts into the new firmware.

## 4. Set up BookOrbit

Go to **Settings → System → BookOrbit Sync** and follow the
[BookOrbit setup](../README.md#setting-up-your-bookorbit-account) in the README. The same
page has **Sync on Wake**, **Sync on Sleep** and **BookOrbit Boot Logo**.

## Updating later

Once this firmware is installed, a new version can be installed the same way (only
`firmware-eego_a4.bin` is needed when the release says so), or with
**Settings → System → Check for Updates**, which looks at this repository's releases.

## Going back to the stock firmware

```bash
python3 -m esptool --chip esp32s3 write_flash 0 eego-a4-stock-16MB.bin
```

## If something goes wrong

- **esptool cannot find or connect to the reader:** try another cable or USB port, eject the
  reader's USB drive first, and run the command again. If it still fails, reconnect the cable
  while holding the power button, then retry.
- **The reader does not start after flashing:** flash all four files again, exactly as in
  step 3. If that does not help, restore your backup.
- **Report problems** in this repository's
  [issues](https://github.com/thebradbishop/CrossInk-Bookorbit/issues), not to EEGO or the
  upstream projects. Include what you did and what you saw.
