# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- SN3218 driver.
- LPD8806 driver.
- Gamma correction to linear dimming output devices.
- Sequential write to SN3218 driver.
- Sequential write to LP55231 driver.
- Name to config for reporting on startup.
- Name to lighting modes to list in serial terminal.
- List of wire devices to info command.

### Changed

- Rename driver files.
- Simplify sequential write in PCA9685 driver.
- Change exponential timing function gamma to match LUT.
- Improve formatting of help command

### Removed

- Command IDs.

## [0.2.0] - 2025-07-25

### Changed

- Convert Sparkplug to run on ESP32

## [0.1.0] - 2025-07-25

### Added

- This CHANGELOG file.
- Initial development.
