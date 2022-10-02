# setcon

Run command with specific selinux context for Android

## Usage

Get prebuilts from [releases](https://github.com/libxzr/setcon/releases).

Push the binary matching your architecture via adb. For example arm64-v8a.
```
$ adb root
$ adb push <path-to-prebuilts>/arm64-v8a/setcon /data
```

Run it and see help.
```
$ adb shell chmod u+x /data/setcon
$ adb shell /data/setcon --help
setcon by LibXZR <i@xzr.moe>
Run command with specific selinux context
Usage:
 setcon <context> <command>
Example:
 setcon u:r:untrusted_app:s0 sh
```

It can be used to test sepolicy.
```
$ adb shell /data/setcon u:r:untrusted_app:s0 ls /
ls: /: Permission denied
$ adb logcat | grep avc
09-27 21:41:08.443 27787 27787 W ls      : type=1400 audit(0.0:180): avc: denied { read } for name="/" dev="dm-2" ino=2 scontext=u:r:untrusted_app:s0 tcontext=u:object_r:rootfs:s0 tclass=dir permissive=0
```

Also a `getcon` binary is included in the prebuilt package. It simply prints current selinux context.
```
$ adb shell /data/getcon
u:r:su:s0
```

## Building

It's easy to build it with [Android NDK](https://developer.android.com/ndk).

```
$ export PATH="/path/to/your/ndk:${PATH}"
$ git clone https://github.com/libxzr/setcon
......
$ cd setcon
$ ndk-build
......
$ tree libs          
libs
├── arm64-v8a
│   ├── getcon
│   └── setcon
├── armeabi-v7a
│   ├── getcon
│   └── setcon
├── x86
│   ├── getcon
│   └── setcon
└── x86_64
    ├── getcon
    └── setcon
```

## Why?

You may wonder we already have `runcon` in [toybox](https://android.googlesource.com/platform/external/toybox), why bother to rewrite?

It's quite interesting that `runcon` itself can be denied by SELinux :)

```
$ adb root
$ adb shell runcon u:r:priv_app:s0:c512,c768 sh
runcon: exec sh: Permission denied
$ adb logcat | grep avc
10-02 18:43:27.027  5376  5376 W runcon  : type=1400 audit(0.0:124): avc: denied { entrypoint } for path="/system/bin/sh" dev="dm-2" ino=539 scontext=u:r:priv_app:s0:c512,c768 tcontext=u:object_r:shell_exec:s0 tclass=file permissive=0
10-02 18:43:27.027  5376  5376 W runcon  : type=1400 audit(0.0:125): avc: denied { entrypoint } for path="/vendor/bin/sh" dev="dm-4" ino=261 scontext=u:r:priv_app:s0:c512,c768 tcontext=u:object_r:vendor_shell_exec:s0 tclass=file permissive=0
```

## License

[MIT](LICENSE)
