# recipe

This contains recipes for AsteroidOS.

To build TDLib or the app you'll first have to setup bitbake, as described [here](https://wiki.asteroidos.org/index.php/Building_AsteroidOS) (additional info [here](https://wiki.asteroidos.org/index.php/OpenEmbedded)). It doesn't seem to be required to do a full OS build using `bitbake asteroid-image`, you can instead proceed with the rest of this guide (but if you experience any issues you could try to run that).

If you're using a container, it is recommended to run full bash shell for easier development. You would also need to not only mount asteroid git repo at /asteroid, but also the Ferniegram repository somewhere. You can do this with the `-v "/host/path/to/harbour-fernschreiber2:/harbour-fernschreiber2"` flag on docker.

Additionally you need to setup the secrets file. See main README for details

# Building TDLib

Note that you can instead download prebuilt TDLib from the link in the main README file.

Clone the TDLib repository somewhere (see main README for more details on this).

First of all, you'll need to generate the source files. This can be done using the `TD_GENERATE_SOURCE_FILES` CMake option. You can use SailfishOS SDK (see main README for details), but in this example we will do it on the host:

- Install all the requirements (see [TDLib build instructions generator for details](https://tdlib.github.io/td/build.html?language=C%2B%2B))
- `cd` into the TDLib directory
- `cmake -DCMAKE_BUILD_TYPE=Release -DTD_GENERATE_SOURCE_FILES=ON ..`
- `cmake --build .`

If you're using a container, forward the TDLib directory to it (using `-v` flag, see above for details), and run the following commands in it.

Assuming TDLib source code is at `/td/` and asteroid repository is at `/asteroid/`

- First, create the initial TDLib recipe: `devtool add tdlib /td/`
- Next, edit the recipe using `devtool edit-recipe tdlib`, or by manually opening the file at `/asteroid/build/workspace/recipes/tdlib/tdlib_git.bb` in your favourite text editor
- Put the contents of the `tdlib.bb` file next to this README in the recipe file
- Run `devtool build tdlib`
- TDLib file will be located at `/asteroid/build/tmp-glibc/work/armv7vehf-neon-oe-linux-gnueabi/tdlib/1.0/package/usr/lib/libtdjson.so.<version>`

# Building Ferniegram

Make sure you have the prebuilt TDLib library in `tdlib/asteroid/lib/`.

- `devtool add asteroid-fernschreiber2`
- Next, edit the recipe using `devtool edit-recipe asteroid-fernschreiber2`, or by manually opening the file at `/asteroid/build/workspace/recipes/tdlib/fernschreiber2_git.bb` in your favourite text editor
- Put the contents of the `asteroid-fernschreiber2.bb` file next to this README in the recipe file
- `devtool build asteroid-fernschreiber2` (might not be needed, the bitbake command is enough sometimes)
- `bitbake asteroid-fernschreiber2`

`.ipk` package will be located at `/asteroid/build/tmp-glibc/deploy/ipk/armv7vehf-neon/asteroid-fernschreiber2_<version>_armv7vehf-neon.ipk`