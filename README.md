# Settle a payment (C++)

Implement `settle` in `src/sum_amounts.cpp`. Plan on 15 minutes. The rules are in [SPEC.md](SPEC.md).

Do not change `include/sum_amounts.hpp` or `tests/test_sum_amounts.cpp`.

## Run

From this directory:

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Submit

This directory is only the C++ task. Create a branch and push it. Do not change `tests/`, `include/sum_amounts.hpp`, `SPEC.md`, or `.github/`.

From this directory:

```bash
git checkout -b candidate/<your-name>
git add src/sum_amounts.cpp
git commit -m "Implement settlement"
git push -u origin candidate/<your-name>
```
