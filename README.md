![](Conception%203D/Vue_generale_droite.PNG)

# Battle Bot project

Création d'un robot de bataille en respectant les règles suivantes :
- Robot roulant => Poids max 900g,
- Dimension max: le robot doit rentrer dans un cube de 25 cm cube avec ou sans partie dépliable,
- Un bouton d'arrêt d'urgence présent et accessible,
- Le robot doit être radiocommandé,
- L'arme doit pouvoir être désactivée via la communication,
- Si le contrôleur est deconnecté du robot, celui-ci s'arrête.

## Notre robot

### Branchement

Le branchement est fait avec: 1 batterie de 14.8V, un ESP32, 4 moteurs, 1 pont en H, 1 moteur shield, 1 servomoteur, 2 abaisseurs de tension qui baisse la tension à 5V (utilisé pour alimenter presque tous les composants) et 3.3V (utilisé pour alimenter l'ESP32 pour fournir assez de puissance).
Il est présent dans la partie **électronique**: fichier schemas_electrique, fait sans les abaisseurs de tension.

### Motorisation

Le robot possède 4 roues équipées chacune d'un moteur. Le train avant est équipé de 2 moteurs à fort couple alimentés en 14V. Le train arrière est équipé de 2 moteurs haut en RPM alimentés en 5V. Le but est de pouvoir manipuler les 2 moteurs avants individuellement: avancer, reculer, tourner à gauche ou tourner à droite. Les 2 moteurs arrières sont contrôlables par pair. Enfin, on peut contrôler les 4 moteurs ensembles  c'est-à-dire que les 4 roues avancent ou reculent en même temps.
Des détails sont disponibles dans le code PS4ProgFinal dans la partie **électonique**.

### Communication / Pilotage
 
Le robot est équipé d'un ESP32 afin de gérer la communication Bluetooth avec la manette PS4 en utilistant une librarie de aed3: https://github.com/aed3/PS4-esp32.

Le robot se déplace avec le stick gauche (Stick L), qui est calclué avec les différentes valeurs obtenus en mettant le stick dans différentes positions (présent dans la partie **électonique**, fichier valeurs_Stick et Stick_L) et avec les conditions définit avec les courbes: y=x et y=-x.
Le pilote a le choix de contrôler les trains individuellement ou contrôler les deux en même temps en fonction du mode de déplacement choisis via la manette PS4. Par exemple, si nous appuyons sur le button Circle de la manette les deux roues arrière rouleront.

Il peut appuyer sur les gâchettes : L1 ou R1 ou les deux en même temps, afin de lever ou baisser l'arme.

### Arme 

Les armes du robot sont gérées via un servomoteur de 15kg de couple alimenté en 5V. Elles sont reliées à ce dernier via un bras et peuvent donc être échangées depuis l'exterieur du robot ce qui facilite leur changement en fonction des épreuves.
Pour l'épreuve des balle de ping pong, nous avons conçu un ramasse balle en forme de pelle à poussière afin de les piéger et de pouvoir en ramasser un maximum avant de les déposer dans la zone de l'arène prévue. 
Pour les duels, nous avons prévu une arme en forme de lance qui peut être relevée et abaissée. Lorsqu'elle est abaissée, elle racle le sol et possède les mêmes avantages qu'une pelle en plus de tenir l'adversaire à distance. Elle peut être relevée afin de faire basculer l'adversaire si celui-ci se trouve dessus.
Les dessins techniques sont disponibles dans la partie **Conception 3D** du dépôt.

### Structure du robot

Le robot possède un étage en plus et est vissé au chassîs. 
Ce dernier abrite le servomoteur en plus d'un emplacement pour la batterie et est troué afin de faire passer les câbles vers le chassîs.
Le chassîs a été conçu afin de contenir les 2 motor shield, les 2 abaisseurs de tension, l'ESP8266 ainsi que les 4
moteurs. Les moteurs avants sont incrustées dans le chassis et vissés dans celui-ci via un adaptateur (cf. Conception 3D/Adaptateur).

Il possède 4 faces dont 3 incurvées afin d'optimiser la contenance du robot et rediriger la poussée du robot adverse vers le haut. Ces 4 faces sont vissées et encastrées dans le chassîs et dans la plaque supérieure. Ces 4 faces sont prévues pour être le plus proche du sol afin de ne pas être soulevé par l'adversaire.

La face avant possède une ouverture verticale afin de faire passer les armes à travers et de ne pas gêner leurs mouvements.
La face arrière possède une fenêtre permettant l'accès au bouton d'arrêt.

La plaque de toit a seulement un but esthétique et s'imbrique dans la plaque supérieure via des plots ce qui facilite l'accès à la batterie et au servomoteur.

Les dessins techniques sont disponibles dans la partie **Conception 3D** du dépôt.
