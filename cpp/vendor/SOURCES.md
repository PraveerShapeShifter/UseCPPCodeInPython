# Vendored C++ sources

Files in this folder are copies of code owned by the main ShapeShifter C++
application (or POC stand-ins until real files are copied in).

Rules:
- Do NOT edit files here to make them build or to fix bugs. Fix upstream in the
  main application, then re-copy, so the two codebases never drift.
- This folder must stay free of pybind11/Python includes. Python-facing code
  lives in `cpp/bindings/`.
- Record every sync in the table below.

| File          | Origin                      | Upstream version/commit | Last synced |
|---------------|-----------------------------|-------------------------|-------------|
| Maths.cpp/.h  | POC stand-in (no upstream)  | -                       | 2026-06-12  |
| Fabric.cpp/.h | POC stand-in (no upstream)  | -                       | 2026-06-12  |
