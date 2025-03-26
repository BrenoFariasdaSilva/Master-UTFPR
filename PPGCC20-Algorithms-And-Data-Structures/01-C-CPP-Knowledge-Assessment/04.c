// 4. Escreva uma função em C que receba um arquivo de texto como parâmetro e conte o número de palavras que começam com a letra 'a'.

void lerArquivo(const char* file_name) {
    FILE* fptr = fopen(*file_name, r);

    char ch;
    int i = 0;
    while ((ch = fgetc(fptr)) != EOF) {
        if (ch = "a" && (fgetc(fptr-1)) = " ")
            i+=1;
    }

    fclose(fptr);

    printf("Count: %d", i);

}
