Repository contains base infrastructure needed for writing a new pass in LLVM.
All credits go to a well known author of [llvm-tutor](https://github.com/banach-space/llvm-tutor)
Most of the code I would say almost all comes from his repository.

# Build pass as shared object
```bash
mkdir build-llvm-pass-infra
cd build-llvm-pass-infra
cmake ../llvm-pass-infra/FirstPassStandalonePlugin/ -DEXTERNAL_LLVM_INSTALL_DIR=<path to llvm install>
make
```

# Run passes over LLVM IR file.

## Old pass manager
```
opt ../llvm-pass-infra/FirstPassStandalonePlugin/inputs/test.ll -load lib/liblegacyhelloworld.so -legacy-hello-world
```

## New pass manager
```
opt ../llvm-pass-infra/FirstPassStandalonePlugin/inputs/test.ll -load-pass-plugin lib/libnewpmhelloworld.so  -passes=new-pm-hello-world
```

