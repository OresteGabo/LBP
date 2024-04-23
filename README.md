# Descripteur d'image : Local Binary Pattern (LBP)

Ce dépôt contient un exemple d'utilisation du descripteur d'image Local Binary Pattern (LBP) en utilisant OpenCV en C++. Le LBP est une technique largement utilisée pour la reconnaissance de textures et de visages, ainsi que pour diverses tâches de vision par ordinateur.

## Description de l'algorithme

L'algorithme LBP consiste à comparer l'intensité des pixels voisins par rapport à un pixel central dans une zone locale de l'image. Ces comparaisons binaires sont ensuite concaténées pour former un motif binaire local pour chaque pixel de l'image.

Les motifs binaires locaux ainsi obtenus sont utilisés comme descripteurs pour caractériser les textures de différentes parties de l'image. Ils sont robustes aux variations d'éclairage et de contraste, ce qui en fait une technique populaire pour la reconnaissance de textures et de visages dans des conditions diverses.

## Utilisation

Pour exécuter le code, assurez-vous d'avoir OpenCV installé. Vous pouvez compiler le code en utilisant un compilateur C++ avec OpenCV lié.

```bash
g++ main.cpp -o image_processing `pkg-config opencv --cflags --libs`
./image_processing
# LBP
