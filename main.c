#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <stdbool.h>
#include <time.h>

#include "pila.h"
#include "login.h"
#include "admin.h"
#include "combos.h"
#include "carrito.h"
#include "struct.h"

int main()
{
    // system("color b4");
    leerUsuario();
    welcome();

    return 0;
}

void welcome()
{
    printf("---- [ Bienvenidos a CINEMACENTER ] ---- ");
    printf("\n");

    int opcion;

    printf("\n[1] ---- Opcion 1 [Registrarme]");
    printf("\n[2] ---- Opcion 2 [Iniciar sesion]");

    printf("\n\nOpcion = ");
    fflush(stdin);
    scanf("%d", &opcion);

    system("cls");

    int sesion;
    Usuario usuarioInicial = {   .id = -1,
                                 .nombreUsuario = "",
                                 .password = "",
                                 .ubicacion = "",
                             };

    switch(opcion)
    {
    case 1:
        crearUsuario();
        notificacion("");
        welcome();
        break;
    case 2:
        usuarioInicial = iniciarSesion(usuarioInicial);
        if(usuarioInicial.id != 0 && usuarioInicial.id != -1)
        {
            notificacion("\n");
            menuPrincipal(usuarioInicial);
        }
        if(usuarioInicial.id == 0)
        {
            puts("\n");
            notificacion("Ingresara a la seccion de administrador");
            menuAdmin();
        }
        if(usuarioInicial.id == -1)
        {
            notificacion("Usuario y contraseņa no coinciden.");
            welcome();
        }

        break;
    default:
        notificacion("Opcion invalida.");
        welcome();
    }
}

void menuPrincipal(Usuario sesion)
{
    printf("---- [ Opciones ] ---- ");
    printf("\n");

    srand(time(NULL));
    int opcion;

    printf("\n[1] ---- Opcion 1 [Ver peliculas disponibles]");
    printf("\n[2] ---- Opcion 2 [Ver mi carrito]");
    printf("\n[3] ---- Opcion 3 [Ver supercombos cinemacenter]");
    printf("\n[4] ---- Opcion 4 [Cerrar sesion]");

    printf("\n\nOpcion = ");
    fflush(stdin);
    scanf("%d", &opcion);

    Pelicula peliculaSeleccionada;
    Ticket ticketSeleccionado;

    system("cls");

    switch(opcion)
    {
    case 1:
        leerPeliculas();
        printf("Ingresar ID de la pelicula que desee agregar al carrito:  ");
        fflush(stdin);
        scanf("%d", &opcion);

        Pelicula peliculaSeleccionada = validarIDPelicula(opcion);
        system("cls");

        if(peliculaSeleccionada.id != 0)
        {
            leerCines();
            printf("Ingresar ID cine que desee agregar al carrito:  ");
            fflush(stdin);
            scanf("%d", &opcion);
            Cine cineSeleccionado = validarIDCine(opcion);
            system("cls");

            if(cineSeleccionado.id != 0)
            {
                crearTicket(sesion, peliculaSeleccionada, cineSeleccionado);
            }
            else
            {
                printf("ID CINE ERRONEO. ");
                system("pause");
                system("cls");
                menuPrincipal(sesion);
            }

        }
        else
        {
            printf("ID PELICULA ERRONEO. ");
            system("pause");
            system("cls");
            menuPrincipal(sesion);
        }
        break;
    case 2:
        leerTicket(sesion);

        printf("Elegir ID de ticket que desea abonar: ");
        fflush(stdin);
        scanf("%d", &opcion);

        Ticket ticketSeleccionado = validarIDTicket(opcion);
        if(ticketSeleccionado.id != 0)
        {
            system("cls");
            puts("-------------------------------------------------");
            printf("Operacion realizada con exito.\n");
            printf("Canjear este codigo en el cine |%d| \n ",rand() );
            puts("-------------------------------------------------");
        }

        puts("\n");
        system("pause");
        notificacion("");
        menuPrincipal(sesion);

        break;
    case 3:
        ingresarCombos();
        break;
    case 4:
        welcome();
        break;
    default:
        notificacion("Debe ingresar una opcion valida");
        menuPrincipal(sesion);
    }
}

void notificacion(char mensaje[30])
{
    puts(mensaje);
    puts("Redireccionando...");
    sleep(2);
    system("cls");
}
