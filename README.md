# HTTP Remote

Ce projet vient répondre aux besoins du Coding Club d'EPITECH.

## La problèmatique

Lors d'un Coding Club, de nombreux participants viennent s'essayer à la programmation. Les "Cobras", formés sur le sujet, encadrent l'évenement.

Dans le cadre de certains sujets, il est interessant pour les encadrants de pouvoir lancer des tests fonctionnels _(moulinettes)_ sur le travail des participants pour en estimer l'avancée.

Deux solutions s'offrent à nous :

- Créer un executable obfusqué, simple d'execution que chaque participant pourrait lancer.
- Transférer le travail vers une de nos machines pour executer les tests localement.

La première solution posait différents problèmes :

- L'executable doit pouvoir marcher sur n'importe quel OS
- L'excutable nécéssite généralement des dépendances et plusieurs fichiers
- Les participants peuvent être amenés à travailler sur leur PC et ne veulent pas forcément installer des tonnes de fichiers et dépendances
- Les encadrants n'ont aucun accès aux résultats de ces tests sans consulter le PC du partcipant

Nous nous sommes naturellement tournés vers la deuxième solution.

## La solution

HTTP Remote est un programme conçu spécialement pour le Coding Club, il n'est pas un exemple de sécurité pour le monde de l'entreprise par exemple mais pour le cadre de ces ateliers, la sécuité est suffisante.

HTTP Remote tire profit de la permissivité du reseau LAN. Il est composé de trois parties :

- Un serveur principal (un PC d'encadrant)
- Des clients (les PC des participants)
- Un panel d'administration (sur le PC serveur)

Le script client est adapté à Windows, MacOS et Linux. Il n'a que très peu de dépendances et se lance très simplement.

Le script serveur va reçevoir les connexions entrantes des scripts clients. Par cette connexion, le serveur va mémoriser les adresses IP locales de chaque ordinateurs clients.

Les scripts clients vont en suite lancer un serveur HTTP sur la machine du participant. Ce serveur pourra reçevoir des requètes du serveur principal et transmettre le contenu des fichiers de travail du participant.

> L'objectif n'est pas d'espionner le PC du participant. Un intervenant ne pourra pas consulter les dossier parents au working directory du script client.

Le panel, lui, envoie des requètes authentifiées au serveur principal. Le serveur questionnera à son tour le client ciblé et retournera les informations demandées...

![](https://cdn.discordapp.com/attachments/843925825317634088/967544558747549696/unknown.png)

Une fois le Coding Club terminé, le participant pourra simplement supprimer le script client de son ordinateur, celui-ci ne laissera aucune trace de son passage sur la machine.
