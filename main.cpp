/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mari-cruz <mari-cruz@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 12:40:50 by mari-cruz         #+#    #+#             */
/*   Updated: 2026/03/17 12:48:34 by mari-cruz        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <unistd.h> // para usleep

int main()
{
    // ASCII grande para ERROR 404
    std::cout << "███████╗██████╗ ███████╗ ██████╗  ██████╗ \n";
    std::cout << "██╔════╝██╔══██╗██╔════╝██╔═══██╗██╔═══██╗\n";
    std::cout << "█████╗  ██████╔╝█████╗  ██║   ██║██║   ██║\n";
    std::cout << "██╔══╝  ██╔═══╝ ██╔══╝  ██║   ██║██║   ██║\n";
    std::cout << "███████╗██║     ███████╗╚██████╔╝╚██████╔╝\n";
    std::cout << "╚══════╝╚═╝     ╚══════╝ ╚═════╝  ╚═════╝\n\n";

    // Muñequito simple
    const char* muñeco[] = {
        " o ",
        "/|\\",
        "/ \\"
    };

    int width = 20; // espacio horizontal de movimiento
    while (true)
    {
        for (int pos = 0; pos < width; ++pos)
        {
            // Borrar pantalla
            std::cout << "\033[2J\033[H";

            // Imprimir ERROR 404 de nuevo arriba
            std::cout << "███████╗██████╗ ███████╗ ██████╗  ██████╗ \n";
            std::cout << "██╔════╝██╔══██╗██╔════╝██╔═══██╗██╔═══██╗\n";
            std::cout << "█████╗  ██████╔╝█████╗  ██║   ██║██║   ██║\n";
            std::cout << "██╔══╝  ██╔═══╝ ██╔══╝  ██║   ██║██║   ██║\n";
            std::cout << "███████╗██║     ███████╗╚██████╔╝╚██████╔╝\n";
            std::cout << "╚══════╝╚═╝     ╚══════╝ ╚═════╝  ╚═════╝\n\n";

            // Espacios para mover muñequito
            for (int i = 0; i < 3; ++i) // 3 líneas del muñeco
            {
                for (int s = 0; s < pos; ++s)
                    std::cout << " ";
                std::cout << muñeco[i] << "\n";
            }

            usleep(100000); // 0.1s de pausa
        }
    }

    return 0;
}