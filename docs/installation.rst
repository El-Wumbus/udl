Installation
============

``udl`` is a cross-platform application with slightly different
installation instructions depending on your Operating System

From PKGBUILDS (Arch Linux)
***************************

.. code:: bash

  git clone https://github.com/el-wumbus/udl.git
  cd udl/archpkg
  makepkg -si

From Releases (Linux/Windows)
*****************************

Download the `latest release
<https://github.com/el-wumbus/udl/releases/latest>`__ for your
platform.

From Source (Linux/macOS)
*************************

Build Dependencies
~~~~~~~~~~~~~~~~~~

- git (To clone the repo)
- gcc (To compile the code)
- make

Build Instructions
~~~~~~~~~~~~~~~~~~

.. code:: bash
  
  git clone https://github.com/el-wumbus/udl.git
  cd udl
  make
  sudo make install

From Source (Windows)
*********************

.. _build-dependencies-1:

Build Dependencies
~~~~~~~~~~~~~~~~~~

- `git <https://github.com/git-for-windows/git/releases/latest>`__
  (To clone the repo)
- `gcc <https://dev.to/gamegods3/how-to-install-gcc-in-windows-10-the-easier-way-422j>`__
  (To compile)
- `make <https://www.technewstoday.com/install-and-use-make-in-windows/>`__

.. _build-instructions-1:

Build Instructions
~~~~~~~~~~~~~~~~~~

.. code:: powershell
  
  git clone "https://github.com/el-wumbus/udl.git"
  Set-Location udl
  make
  mv dist\udl dist\udl.exe

The location of the portable binary is ``dist/udl.exe``
  