#include "prototypes.h"

SOCKET csock;
SOCKET sock ;
SOCKADDR_IN sin;
SOCKADDR_IN csin;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;

/**
*
*   Fonctions Socket
*
*   creation du multi thread
*
*   thread 1 ecoute du port reception_message()
*   thread 2 emission de message emission_message()
*
*
*   Bryann Brovia
**/



//partie fonctions pour le client ;
void* reception_message(void* data_Clt_in) {

    GameObject information_ennemy  ;
    while(1){

    // Si l'on reçoit des informations : on les affiche à l'écran
        if(recv(csock, &information_ennemy, sizeof(information_ennemy), 0) != -1) {

            if(information_ennemy.spell == 1 ){
                // affiche le nouveau spell
                createSpell(information_ennemy, ENNEMY) ;

            }
            setEnnemy(information_ennemy) ;

            /**
            *
            *   traitemetn de message_recu
            *
            ***/
         } else {
            printf("erreur dans la reception du message") ;
            //erreur de transmission
        }

    }
}

void* emission_message(void* data_Clt_out) {

    while(1){

        int sock_err ;
        int frameLimit = SDL_GetTicks() + 16;
        delay(frameLimit);
        frameLimit = SDL_GetTicks() + 16;

        // send () retourne -1 en cas d'erreur sinon elle retourne le nombre d'octets envoyés
        if(( send(csock, getPlayer(), sizeof(GameObject), 0) )  == -1){
            printf("Erreur de transmission 1 \n");
        } else {
            //resetPlayerSpell() ;
            //printf("erreur dans l'envoie des informations socket.c 98") ;
        }

        if(getPlayerSpell() == 1) {
            setPlayerSpell(0) ;
        }
    }

   return NULL;
}

void* serveurEnAttente(void* data_Clt_out) {

    /**
    *
    *   Declaration des variables Sockets
    *
    **/
    //socket de la machine

    int sock_err;
    int erreur = 0 ;

    // Si la socket est valide
    // AF_INET pour le protocole TCP
    // SOCK_STREAM pour le protocole TCP

    if((sock = socket(AF_INET, SOCK_STREAM, 0)) != -1) {

        printf("Serveur en attente de connexion socket.c 113") ;

        // Creation d'un thread didée a l'ecoute de nouvelle connexion
        pthread_t th_ouvertureCommunicationServeur;
        pthread_create(&th_ouvertureCommunicationServeur, NULL, ouvertureCommunicationServeur, NULL);

    } else {

        printf("Erreur initialisation de la socket\n");
    }

}

void* ouvertureCommunicationServeur(void* data_Srv) {

    printf("OuvertureCommunicationServeur") ;
    socklen_t recsize = sizeof(csin);

    /* Configuration */

    //sin.sin_addr.s_addr => ip du serveur crée
    //htonl(INADDR_ANY) => adress ip automatique
    //inet_addr(chaine de caractere) => forcer une adresse ip
    sin.sin_addr.s_addr    = htonl(INADDR_ANY) ;
    // sin.sin_family => Format de l'adresse
    //AF_INET => Format Adresse IP
    sin.sin_family         = AF_INET;
    //sin.port => port utilisé
    //htons(port) => sera le port utilisé
    sin.sin_port           = htons(PORT);

    // bind() => permet d'ccassocie les informations precedentes au la socket crée au paravant
    // sock => La socket dont on modifie les parametres
    // (SOCKADDR*)&sin => le pointeur sur la structure sockaddr du serveur
    // sizeod(sin) => la taille de la memoir occuper par le contexted'adressage du serveur
    printf("\n parametre socket serveur : %d %d %d", sin.sin_addr , sin.sin_family , sin.sin_port) ;
    if(( bind(sock, (SOCKADDR*)&sin, sizeof(sin)) ) != -1) {
        // Si la socket fonctionne

        // listen() => Démarrage du listage (mode server)
        // sock => Designe la socket qui va etre utiliser
        // 5 => backlog le nombre de connexions pouvant etre mise en attente
        // les clients ftp pouvant accepter 5 connexions en attente
        listen(sock, 5);
        printf("socket serveur initialise socket.c 162")  ;

        // accept()
            // retourne -1 en cas d'erreur ou INVALID_SOCKET
            // sock => le socket serveur utilisé
            // (SOCKADDR*)&csin => le pointeur sur l'adresse du client
            // &recsize IDEM bind
        if(csock = accept(sock, (SOCKADDR*)&csin, &recsize)){

            //initializeEnnemy(600,600) ;
            //setEnnemy();
            // Chat emmission/reception

            // On crée un thread Client
            pthread_t th_reception;
            pthread_t th_emission;

            // Permet d'exécuter le fonction {reception_Clt;emission_Clt} en parallèle
            pthread_create(&th_reception, NULL, reception_message, NULL);
            pthread_create(&th_emission, NULL, emission_message, NULL);

            // Attend la fin du thread créé
            pthread_join(th_reception, NULL);
            pthread_join(th_emission, NULL);
        } else {
            printf("la demande de connexion du client a echoué socket.c 186") ;
        }
    } else {
        printf("erreur dans l'initialisation de la socket serveur socket.c 189\n ") ;
    }

   return NULL;

}

void ouvertureCommunicationClient() {

    printf("initialisation de la socket client socket.c 187\n") ;

    char *address_Sev[20] ;

    printf("saisir IP serveur : ") ;
    scanf("%s", address_Sev) ;
    socklen_t recsize = sizeof(csin);
    // Création de la socket
    csock = socket(AF_INET, SOCK_STREAM, 0);

    if(csock)
        printf("socket client ok socket.c 212") ;

    sin.sin_addr.s_addr = inet_addr(address_Sev);
    sin.sin_family = AF_INET;
    sin.sin_port = htons(PORT);



    if(connect(csock, (SOCKADDR*)&sin, sizeof(sin)) != -1) {

        printf("connected") ;
        // On crée un thread Client
        pthread_t th_ouvertureClient;
        // Permet d'exécuter le fonction {reception_Clt;emission_Clt} en parallèle
        pthread_create(&th_ouvertureClient, NULL, ouvertureClient, NULL);
        setOnMenu(0) ;

        initializeGameobject(getEnnemy(), ENNEMY , 3 , RIGHT , 0 ,0 , 0 , 8, TIME_BETWEEN_2_FRAMES_PLAYER , 125 , 180 , PLAYER_WIDTH , PLAYER_HEIGTH , NULL);
        initializeGameobject(getPlayer(), PLAYER, 3 , RIGHT , 0 ,0 , 0 , 8, TIME_BETWEEN_2_FRAMES_PLAYER , 1000 , 655 , PLAYER_WIDTH , PLAYER_HEIGTH, NULL);


    } else {
        printf("Impossible de se connecter\n");
    }
}

void* ouvertureClient(void *data) {

      // On crée un thread Client
        pthread_t th_reception;
        pthread_t th_emission;

        // Permet d'exécuter le fonction {reception_Clt;emission_Clt} en parallèle
        pthread_create(&th_reception, NULL, reception_message, NULL);
        pthread_create(&th_emission, NULL, emission_message, NULL);

        // Attend la fin du thread créé
        pthread_join(th_reception, NULL);
        pthread_join(th_emission, NULL);

}

void onServeur(void) {
    /**
    *
    *   Creation d'un thread ( execution parallele) qui met le serveur en attente de connexion
    *
    **/
   // printf("creation du thread en attente de connexion th_serveurEnAttente\n");
    pthread_t th_serveurEnAttente;
    //appelle de la fonction serveurEnAttente voir socket.c
    pthread_create(&th_serveurEnAttente, NULL, serveurEnAttente, NULL);
    // Attend la fin du thread créé
    pthread_join(th_serveurEnAttente, NULL);

    //initializePlayer(1);
    initializeGameobject(getPlayer(), PLAYER , 3 , RIGHT , 0 ,0 , 0 , 8, TIME_BETWEEN_2_FRAMES_PLAYER , 115 , 125 , PLAYER_WIDTH , PLAYER_HEIGTH , NULL);
    initializeGameobject(getEnnemy(), PLAYER , 3 , RIGHT , 0 ,0 , 0 , 8, TIME_BETWEEN_2_FRAMES_PLAYER , 1000 , 655 , PLAYER_WIDTH , PLAYER_HEIGTH , NULL );
    //changeLevel();
    setOnMenu(0) ;

}

void onClient() {

    ouvertureCommunicationClient() ;
}

