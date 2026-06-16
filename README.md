# ShapeShifter native modules

C++ (Win32/MFC/ATL) functionality exposed to Python via pybind11, consumed by
the ShapeShifter Flask backend. Windows-only by design.

## Layout

```
cpp/
  vendor/      C++ sources copied from the main ShapeShifter application.
               Pure C++ — no pybind11/Python here. See vendor/SOURCES.md.
  bindings/    pybind11 binding code, one file per Python module.
               PYBIND11_MODULE lives only here.
  inc/         Project-owned headers (NOT copied from upstream): glue such as
               cstring_caster.h (CString <-> str), plus thin wrapper classes
               over the vendored functions, e.g. FabricWrapper.h (class Fabric).
shapeshifter/  The Python package. Built .pyd extensions land here.
tests/         pytest regression suite. Run after every build (and in CI).
examples/      flask_api.py — reference for the Flask backend integration.
.github/       workflows/ci.yml builds the extensions and runs pytest on push/PR.
```

## Build (development)

```
python setup.py build_ext --inplace
python -m pytest
```

## Continuous integration

`.github/workflows/ci.yml` runs this same build + pytest on every push to
`main`/`master` and on pull requests. It runs on `windows-latest` (the
extensions need MSVC + ATL) across a small Python version matrix. Keep the
suite green — a red build blocks merges.

## Install into the Flask backend's environment

```
pip install .
```

Then in Flask code: `from shapeshifter import fabric, maths`.

## Adding a new module

1. Copy the needed `.cpp`/`.h` from the main app into `cpp/vendor/`
   (record it in `cpp/vendor/SOURCES.md`; never edit vendored files here).
2. Create `cpp/bindings/<name>_bindings.cpp` with `PYBIND11_MODULE(<name>, m)`.
   Convert MFC/ATL types at this boundary only (`cstring_caster.h` handles
   CString automatically).
3. Add a `Pybind11Extension("shapeshifter.<name>", [...], **COMMON)` to
   `setup.py`.
4. Add `tests/test_<name>.py`, build, run pytest.

## Debugging

Python-side issues: debug normally (VS Code `debugpy` configs are in
`.vscode/launch.json`).

C++-side issues need a symbols build first:

```powershell
$env:SHAPESHIFTER_DEBUG = "1"
python setup.py build_ext --inplace --force
```

This compiles with `/Zi /Od` and links with `/DEBUG`, producing `.pdb` files so
debuggers map the running `.pyd` back to the C++ source. Rebuild without the
variable (plus `--force`) to return to optimized binaries.

Then pick a debugger:

- **Visual Studio (best for C++):** Debug > Attach to Process > `python.exe`,
  code type "Native". Breakpoints in `cpp/` source hit when Python calls in.
  With the VS Python workload installed, choose "Python + Native" for
  mixed-mode debugging (step from Python directly into C++).
- **VS Code:** start any Python config from `launch.json`, then run the
  "C++: attach to running python.exe" config in a second window and pick the
  python process. Set breakpoints in the `.cpp` files.

Crashes (access violations) kill the Python process and bypass Python
exceptions entirely:

- `faulthandler.enable()` is wired into `examples/flask_api.py` — on a crash it
  prints the Python stack that was executing. pytest enables this by default.
- For the crash location on the C++ side, run under the Visual Studio debugger
  (above); it breaks at the faulting line when symbols are loaded.

Caution: never use `python setup.py build_ext --debug` on Windows — it links
against `python314_d.lib`, which requires a debug build of Python itself.

## Deployment notes (Windows Server)

- Serve Flask with **waitress** behind IIS (ARR reverse proxy or
  HttpPlatformHandler). gunicorn does not run on Windows.
- The server needs the VC++ Redistributable (and MFC DLLs) matching the
  build toolset, and the same Python version/architecture (x64) as the build.
- Release the GIL around long-running C++ calls
  (`py::call_guard<py::gil_scoped_release>()`) before real workloads arrive.
- Verify any vendored code is x64 and thread-safe before exposing it.
