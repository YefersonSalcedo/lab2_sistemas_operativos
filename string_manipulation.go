/*
 * Laboratorio 2 - Sistemas Operativos - Universidad de Antioquia
 *
 * Autores: Yeferson Alexis Salcedo Preciado
 *          Jhoan Esteban Echeverri Villa
 */

package main

import (
	"fmt"
	"os"
	"unicode"
)

const MAX_LEN = 100

func main() {
	if len(os.Args) < 2 {
		fmt.Fprintf(os.Stderr, "Uso: %s \"cadena a procesar\"\n", os.Args[0])
		os.Exit(1)
	}

	buffer := make([]byte, MAX_LEN+1)
	
	input := os.Args[1]
	i := 0
	for i < len(input) && i < MAX_LEN {
		buffer[i] = input[i]
		i++
	}
	buffer[i] = 0 // null terminator


	p_read := 0   // indice de lectura
	p_write := 0  // indice de escritura

	for p_read < MAX_LEN && buffer[p_read] != 0 {
		if unicode.IsLetter(rune(buffer[p_read])) || buffer[p_read] == ' ' {
			buffer[p_write] = buffer[p_read]
			p_write++
		}
		p_read++
	}
	buffer[p_write] = 0 // cerramos la cadena filtrada
	length := p_write      // longitud de la cadena filtrada

	if length == 0 {
		fmt.Println("(vacia) 0 0 (vacia)")
		return
	}

	inicio := 0
	fin := length - 1
	for inicio < fin {
		temp := buffer[inicio]
		buffer[inicio] = buffer[fin]
		buffer[fin] = temp
		inicio++
		fin--
	}
	reversed := string(buffer[:length])

	countA := 0
	countE := 0
	countI := 0
	countO := 0
	countU := 0
	consonantes := 0

	p := 0
	for p < length {
		if buffer[p] != ' ' {
			c := unicode.ToLower(rune(buffer[p]))
			if unicode.IsLetter(c) {
				switch c {
				case 'a':
					countA++
				case 'e':
					countE++
				case 'i':
					countI++
				case 'o':
					countO++
				case 'u':
					countU++
				default:
					consonantes++
				}
			}
		}
		p++
	}
	totalVocales := countA + countE + countI + countO + countU

	p2 := 0
	for p2 < length {
		if buffer[p2] == ' ' {
			buffer[p2] = '_'
		}
		p2++
	}
	modified := string(buffer[:length])

	fmt.Printf("%s %d", reversed, totalVocales)
	if countA > 0 {
		fmt.Printf(" %d", countA)
	}
	if countE > 0 {
		fmt.Printf(" %d", countE)
	}
	if countI > 0 {
		fmt.Printf(" %d", countI)
	}
	if countO > 0 {
		fmt.Printf(" %d", countO)
	}
	if countU > 0 {
		fmt.Printf(" %d", countU)
	}
	fmt.Printf(" %d %s\n", consonantes, modified)
}
