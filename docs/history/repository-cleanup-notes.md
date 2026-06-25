# Repository Cleanup Notes

This file keeps maintenance notes that should not be displayed on the GitHub front page.

## Cleanup Status

To make the GitHub record easier to read:

- The root README is now the current final entry point.
- Old operation documents were moved to `docs/history/`.
- Old startup scripts were moved to `archive/legacy_scripts/`.
- Hardware debug scripts were moved to `tools/hardware_debug/`.
- `logs/*.log` were removed from Git tracking, and `.gitignore` now includes `logs/`.

## Rename Recommendation

For documentation only, the root README corrects `arm gripper` to `STAFF gripper`.

If the directory or package name is truly changed later, update all of these together:

```text
directory name
package.xml <name>
setup.py package_name
setup.cfg script_dir / install_scripts
Python import path
console_scripts
all ros2 run commands
all documentation and test imports
```

Recommended route:

```text
src/r1_arm_control
  -> src/r1_mechanism_control

r1_arm_control package
  -> r1_mechanism_control
```

Do not rename the whole package to `staff_gripper_control`, because it also owns KFS elevator and KFS horizontal control.
