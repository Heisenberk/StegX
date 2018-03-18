<!-- ![Logo](https://raw.githubusercontent.com/Heisenberk/StegX/dev-cmake/doc/rsc/readme-logo.png)  -->
<p align="center">
<img src="https://raw.githubusercontent.com/Heisenberk/StegX/dev/doc/rsc/logo-readme.png">
</p>

---

Introduction
================================================================================

**StegX** est une application de stéganographie. Elle permet de dissimuler des
données dans divers formats de fichier, de type image, son ou vidéo. Les
données cachées peuvent ainsi être transmises par un canal non sécurisé sans
être découverte, puis le receveur pourra les extraire. L'application se compose
d'une interface graphique et d'une interface en ligne de commande, ainsi que
d'une bibliothèque partagée intégrable dans d'autres projets de développement.

Statut
--------------------------------------------------------------------------------

* Interface graphique : développement non commencé.
* Interface en ligne de commande : développement non commencé.
* Bibliothèque : développement non commencé.


---

Installation
================================================================================

Binaires
--------------------------------------------------------------------------------

### -- Unix (Debian-like)

#### - Installateur

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.deb`.
2. Installer le en utilisant une interface à APT (par exemple en double cliquant
dessus), ou en utilisant la commande `sudo apt-get install ./StegX-xxx.deb`
depuis le répertoire de téléchargement.

#### - Portable

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.tar.gz` (archive
tar) ou `StegX-xxx.sh` (exécutable auto extractible).
2. Décompresser l'archive avec la commande `tar xzvf StegX-xxx.tar.gz` ou lancer
l'extraction de l'exécutable avec la commande `./StegX-xxx.sh` en fonction de
votre choix de téléchargement.
3. Vous trouverez un dossier contenant l'application. 

### -- Windows

#### - Installateur

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.exe`.
2. Installer le en double cliquant dessus.
3. Si vous voulez pouvoir lancer l'interface en ligne de commande depuis le
terminal avec la commande `stegx`, alors sélectionner `Ajouter le répertoire
d'installation au PATH` lorsque cela vous sera demandé lors de l'installation.

#### - Portable

1. Dans la section `Release`, téléchargez le fichier `StegX-xxx.zip` (archive
compressée).
2. Décompresser l'archive, ainsi vous trouverez un dossier contenant
l'application. 

Code source
--------------------------------------------------------------------------------

Ces commandes auront pour effet de créer un nouveau répertoire et de s'y placer,
de générer les fichiers de production du projet, de lancer la compilation à
l'intérieur de ce dossier, puis enfin de lancer l'installation.

Si une erreur survient sur **Windows**, faites attention de placer le dossier
dans un chemin qui ne contient pas d'espaces. Certains modules de **CMake** pour
**Windows** gèrent mal les espaces.

Exécuter les commandes suivantes en tant qu'*administrateur* depuis le répertoire
racine de projet (ce qui est entre [  ] est optionnel) :

### -- Unix (Debian-like)

    mkdir build && cd build
    cmake .. [-G "Unix Makefiles"] [-DCMAKE_INSTALL_PREFIX=/usr/local]
    make [all]
    sudo make install

### -- Windows

    mkdir build && cd build
    cmake .. [-G "Visual Studio 15 2017"] [-DCMAKE_INSTALL_PREFIX=/usr/local]
    cmake --build . --target ALL_BUILD
    cmake --build . --target INSTALL

---

Désinstallation
================================================================================

Binaires
--------------------------------------------------------------------------------

### -- Unix (Debian-like)

Exécuter la commande `sudo apt remove stegx` pour supprimer le paquet de votre
système.

### -- Windows

Accéder au panneau de configuration, cliquer sur désinstaller un programme,
sélectionner `StegX` et cliquer sur désinstaller.

Code source
--------------------------------------------------------------------------------

Ces commandes doivent être lancés dans le dossier du projet qui avait servit à
installer l'application depuis les sources. Si vous n'avez plus ce dossier,
alors réinstaller l'application depuis les sources par dessus l'ancienne
installation en suivant les commandes dans la section installation, puis ensuite
procéder à l'installation comme ci-dessus.

Exécuter les commandes suivantes depuis le répertoire source du projet :

### -- Unix (Debian-like)

    cd build
    sudo make uninstall

### -- Windows

    cd build
    cmake --build . --target uninstall

---

Utilisation
================================================================================

Après une installation avec un installateur
--------------------------------------------------------------------------------

Dans un terminal, utiliser la commande `stegx` pour utiliser l'interface en
ligne de commande. Pour lancer l'interface graphique, taper `stegx-gui` dans
votre terminal, ou utiliser le raccourci créer dans le menu démarrer ou sur le
bureau.

Après décompression de la version portable
--------------------------------------------------------------------------------

Placez vous dans le répertoire racine de l'application ou dans le répertoire
`bin`, puis exécutez dans votre terminal `./stegx` pour l'interface en ligne de
commande ou `./stegx-gui` pour l'interface graphique.

Aide
--------------------------------------------------------------------------------

Pour obtenir de l'aide, consulter le manuel de l'interface graphique (PDF), ou
taper dans votre terminal `man stegx` pour lire le manuel de l'interface en
ligne de commande sur **Unix** si l'installation à été effectuée par l'installateur.

---

Développement
================================================================================

Dépendances
--------------------------------------------------------------------------------

### -- Requises

* *Compilateur* : **GNU Compiler Collection** (GCC) (Unix) ou **Microsoft Visual
  Studio C** (MSVC) (Windows)
* *Moteur de production* : **CMake** (Unix & Windows) et **GNU Make** (Unix)
* *Interface graphique* : <b> GTK+ </b> (Unix & Windows)

### -- Optionnelles

* *Générateur de documentation* : **Doxygen** (Unix & Windows)
* *Distribution LaTeX* : **TeX Live** (Unix & Windows)
* *Test unitaire* : **CMocka** (Unix & Windows)

Commandes et cibles
--------------------------------------------------------------------------------

* La configuration de la compilation est à faire en première. Toutes les autres
  commandes sont à effectuer dans le dossier _build_. Lors d'un ajout d'un
  fichier source au projet, ou lors d'une rencontre avec un bug lors de la
  configuration/compilation, supprimez le dossier _build_ et recommencez la
  configuration.
* Les commandes entre [  ] sont optionnelles.
* Si une erreur survient sur **Windows**, faites attention de placer le dossier
  dans un chemin qui ne contient pas d'espaces. Certains modules de **CMake**
  pour **Windows** gèrent mal les espaces.
* Les cibles (targets) exécutées par **CMake** peuvent aussi êtres générées dans
  **MSVC** sous forme de solution portant le même nom sous **Windows**.
* L'option -DVarName=VarValue de **CMake** permet de configurer une variable.
  Ci-dessous une liste des variables configurables avec leurs valeurs possibles :
  1. *Description* : **VarName** = VarValue1, VarValue2 etc...
  2. *Chemin vers un dossier existant pour l'installation* :
  **CMAKE_INSTALL_PREFIX** = /usr/local, /opt/stegx
  3. *Mode de compilation* : **CMAKE_BUILD_TYPE** = Release, Debug

### -- Configuration de la compilation

#### - Unix

    mkdir build
    cd build
    cmake .. [-G "Unix Makefiles"] [-DVarName=VarValue]

#### - Windows

    mkdir build
    cd build
    cmake .. [-G "Visual Studio 15 2017"] [-DVarName=VarValue]

### -- Compilation des modules principaux

#### - Unix

    make [all] [stegx-cli stegx-gui stegx-lib]

#### - Windows

    cmake --build . --target ALL_BUILD [stegx-cli stegx-gui stegx-lib]

### -- Génération de la documentation

#### - Unix

    make doc

#### - Windows

    cmake --build . --target doc

### -- Génération des rapports

#### - Unix

    make report

#### - Windows

    cmake --build . --target report

### -- Lancement des tests unitaires

#### - Unix

    make check

#### - Windows

    cmake --build . --target check

### -- Création des binaires de distribution

#### - Unix

    sudo make dist

#### - Windows

    cmake --build . --target dist // En tant qu'administrateur

### -- Installation

#### - Unix

    sudo make install

#### - Windows

    cmake --build . --target INSTALL // En tant qu'administrateur

### -- Désinstallation

#### - Unix

    sudo make uninstall

#### - Windows

    cmake --build . --target uninstall // En tant qu'administrateur

### -- Nettoyage

#### - Unix

    make clean

#### - Windows

    cmake --build . --target clean
