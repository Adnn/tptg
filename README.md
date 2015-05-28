# TeaParty : A tale of two balls #

##Dependencies##
* [aunteater](https://github.com/Adnn/aunteater)
* [Polycode](https://github.com/ivansafrin/Polycode)

##Prerequisites##

**Install CMake**

See [http://www.cmake.org/download/](http://www.cmake.org/download/)

**Install VS2013 Nov CTP (Windows)**

In order to compile on Windows, you need at least Visual Studio 2013, with the Nov 2013 CTP compiler (to support some C++ 11/14 extensions).

Donwload : [https://www.microsoft.com/en-us/download/details.aspx?id=41151](https://www.microsoft.com/en-us/download/details.aspx?id=41151)

If you are using a newer version of VS, you should be fine as-is.

##How to build Tea Party



**Build Polycode and dependencies** 

See [https://github.com/ivansafrin/Polycode/blob/master/BUILD.md](https://github.com/ivansafrin/Polycode/blob/master/BUILD.md)

Notes : 


- Do not attempt to clone/build Polycode in a long path or ALL_BUILD will fail due to paths longer than 256 chr.


**Build anteater**

	git clone git@github.com:Adnn/aunteater.git

- Get the develop branch

	git checkout develop

- Download the latest Boost libraries [http://www.boost.org/](http://www.boost.org/)
- Unzip it somewhere on your filesystem
- Using CMake-gui, set the source code folder to your anteater folder, the build folder to a /build subfolder in your anteater folder
- Then, in CMake-gui add a new entry (Add Entry) called Boost\_INCLUDE\_DIR, or type "Filepath", pointing to the folder where you unzipped Boost (typically boost_1_58_0)
- Click "Generate"

**Build TPTG**

Open CMake-gui, set the source and build path.

Example : 

- source : "D:/Dev/Tea/tptg"
- build : "D:/Dev/Tea/tptg/build"

Then setup the following variables :

- aunteater\_DIR : "{path\_to\_aunteater}/out/cmake"
- Polycode\_CMAKE\_DIR : "{path\_to\_Polycode}/CMake"
- Polycode\_INCLUDE\_DIR : "{path\_to\_Polycode}/Release/Windows/Framework/Core/include"

Click Configure then Generate.
You can now open the generated TeaParty.sln on your build folder.

**Troubleshooting**

_OPENAL32.dll (Windows)_

When running the binary from the IDE, OpenAL32.dll won't be found.
Copy the file from the generated Polycode dependencies :

	{path_to_Polycode}\Release\Windows\Framework\Core\Dependencies\bin	

to your build folder :

	{path_to_tptg}\build\bin\(Debug|Release)