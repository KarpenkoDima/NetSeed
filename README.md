# NetSeed (Development Branch)

Branch status: **In active development**

## Project Structure (Current)

```
NetSeed/
├── core/                   # Core project files
│   ├── include/           # Header files
│   └── memory/            # Memory Manager (mbuf and others)
│   
│
└── sprouts/               # Examples and tests
    └── tests/        # Debugging utilities

```

## Planned Structure Changes

The following structural changes are planned:

1. New directories to be added:
```
├── tests/                 # Unit and integration tests
├── benchmarks/           # Performance benchmarks
└── scripts/              # Build and utility scripts
```

2. Restructuring of existing directories:
```
├── core/
│   ├── memory/          # Memory management (including mbuf)
│   ├── protocol/        # Protocol implementations
│   └── platform/        # Platform-specific code
```

## Development Setup

1. Clone and switch to develop branch:
```bash
git clone https://github.com/your-username/netseed.git
cd netseed
git checkout develop
```

2. Create build directory:
```bash
mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Debug ..
make -j$(nproc)
```

## Current Focus Areas

- [ ] Memory management optimization
- [ ] Driver architecture refactoring
- [ ] Test framework implementation
- [ ] Documentation system setup


