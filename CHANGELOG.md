# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added

- Additional keycodes and scancodes, awaiting code generation.

### Changed

- `group::membership` revocation now requires calling the membership.
- `input`-based subscriptions based on `group` require calling the membership
  for revocation.

## [1.0.0] - 2024-05-22

### Added

- Keyboard input abstraction module.
- Input indirection support module.
- Documented Planning Diagram.
- First-class `rect`, `point`, and `color` structures.
- Process-loop FPS parameterization.

### Changed

- Renderer function templates now accept concept-restricted types.

### Fixed

- Link-time issues related to `font` and `texture`.
