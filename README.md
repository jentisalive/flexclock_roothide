# FlexClock for RootHide

Replaces the iOS lock screen clock with images, and lets you install your own digit packs.

Native RootHide source port: no RootHide Patcher conversion is needed.
Built against the `CoverSheetKit` lock screen, for iOS 18. This port does not
add support for iOS 15–17; the original firmware restriction is preserved.

![FlexClock on the lock screen](screenshot.png)

## Features

- Animated (GIF or APNG) or static digits
- Adjustable animation speed
- Installable digit packs, imported and removed from Settings
- Optional switch to still frames while Low Power Mode is on
- Adjustable digit size, spacing and vertical offset
- 12-hour / 24-hour / system time format
- Optional date hiding
- Colour tinting that keeps the artwork's shading, the way iOS tints app icons
- Settings apply live, no respring needed
- Falls back to the stock clock if the selected pack is missing or broken

## Requirements

- iOS 18 with a compatible RootHide jailbreak/injection environment
- RootHide versions of the dependencies below
- `preferenceloader`
- ElleKit / Substrate

## Installation

Build this fork as described below, or download the `flexclock-roothide` artifact
from a successful **Build RootHide package** run in this repository's Actions tab.
Unzip the artifact and open the `iphoneos-arm64e.deb` in Sileo inside RootHide.
The upstream repository serves the original rootless package, not this port.

Remove the original package or a Patcher-converted copy before installing this
build. The package identifier is unchanged, so they cannot coexist. Respring
after installation. Do not run this package through RootHide Patcher.

Settings live under **Settings → FlexClock**.

## Digit packs

Four packs ship with the tweak — **Anime**, **Pixel**, **CRT** and **Sakura** —
and Anime is the default.

Packs are plain folders. The bundled ones live here:

```
<jbroot>/Library/Application Support/FlexClock/Packs/
```

Imported ones live outside it, so they survive updates and can be managed from
Settings:

```
<jbroot>/var/mobile/Library/FlexClock/Packs/
```

`<jbroot>` is RootHide's randomized jailbreak root. Both the tweak and Settings
resolve it at runtime with `jbroot()`; do not hardcode its current location.
The installer creates the imported-pack directory inside that root and assigns
it to `mobile`. Existing packs from a regular rootless installation are not
moved automatically; import them again from Settings.

A user pack shadows a bundled pack of the same name, so the included artwork can
be replaced without touching the installed package.

A pack is a folder whose name ends in `.flexpack`:

```
MyPack.flexpack/
├── Info.plist
├── animated/          # optional
│   ├── 0.gif … 9.gif
│   └── colon.gif
└── static/            # optional
    ├── 0.png … 9.png
    └── colon.png
```

- At least one of `animated/` or `static/` must exist. If the folder for the
  selected animation style is missing, the other one is used.
- `.gif` and `.png` are both accepted in either folder, and animated GIF and
  APNG both play at their own frame timing. APNG is worth the larger files when
  the artwork has soft edges: GIF carries a single bit of alpha, which turns a
  glow into a ragged halo. A glyph is looked up as `.gif` first, so a pack
  ships one format or the other, not both.
- Digits are laid out by their aspect ratio, so frames do not have to be square
  or share a common width.
- `Info.plist` is optional; without it the folder name is used as the title.

```xml
<dict>
    <key>Name</key>    <string>My Pack</string>
    <key>Version</key> <string>1.0</string>
</dict>
```

**Settings → FlexClock → Manage packs** lists what is installed, imports a pack
folder and removes the imported ones. A folder is only accepted if it actually
contains digits; if the pack sits one level below what you picked, it is found
there. Copying a folder into the directory above works just as well.

Packs can also be shipped as `.deb` packages that install into the bundled
directory.

## Building

Requires [RootHide Theos](https://github.com/roothide/theos), its headers and
libraries, and the patched iPhoneOS 16.5 SDK. On macOS, install Xcode and `ldid`.
A current Xcode toolchain is recommended for the arm64e ABI.

```sh
git clone --recursive https://github.com/roothide/theos.git "$HOME/theos-roothide"
export THEOS="$HOME/theos-roothide"
"$THEOS/bin/install-sdk" iPhoneOS16.5
make clean
make package FINALPACKAGE=1
```

The default scheme is `roothide`. The output is
`packages/com.tr3tol.flexclock_1.0.2+roothide1_iphoneos-arm64e.deb`.
Both the tweak and preference bundle explicitly link `libroothide`, including
when clang modules are disabled. The package payload uses `/Library` paths;
RootHide's package manager installs these under its own root.

A regular rootless build is still available with
`make clean && make package FINALPACKAGE=1 THEOS_PACKAGE_SCHEME=rootless`.
It uses `/var/jb` for package resources and the original system mobile directory
for imported packs. Theos sets the package architecture for that scheme.

## Validation

The GitHub Actions workflow builds and checks the RootHide package metadata and
layout, then uploads the `.deb`. A successful build does not replace on-device
validation: check injection into SpringBoard, Settings → FlexClock, all bundled
packs, importing/deleting a pack, and live preference updates. After a jailbreak
root change, check that bundled and imported packs still resolve correctly.

## Credits

- Idea — [yandevelop](https://github.com/yandevelop), author of the original
  AniTime tweak. FlexClock is an independent reimplementation for modern iOS.
- Development — [tr3tol](https://github.com/tr3tol)

## License

Source code is released under the GNU General Public License v3.0, see
[LICENSE](LICENSE). Bundled digit artwork is not covered by it and remains the
property of its respective authors.
