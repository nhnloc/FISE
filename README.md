# Multi threaded file indexing & Search engine
A high-performance Linux CLI tool that recursively scans directories, indexes files, and supports fast keyword-based search using multithreading and modern C++ OOP design.

---

## Features
- Multithreaded file scanning with 'std::thread' and custom 'ThreadPool'
- Inverted index for fast keyword search
- Modular OOP architecture
- POSIX-compliant file traversal (`std::filesystem`)
- CLI interface with subcommands: `--scan`, `--search`, `--help`
- Thread-safe logging system

