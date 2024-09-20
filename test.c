#include "minishell.h"

char *add_spaces2(t_data *data) 
{
    int i = 0;
    int j = 0;
    int len = ft_strlen(data->line);
    int new_len = 0;

    // First pass to calculate the length of the new string
    while (i < len) {
        if (data->line[i] == ' ') {
            while (data->line[i] == ' ')
                i++;
        }
        
        if ((data->line[i] == '>' && data->line[i + 1] == '>') ||
            (data->line[i] == '<' && data->line[i + 1] == '<')) {
            new_len += 3; // " >> " or " << " plus spaces
            i += 2;
        } else if (data->line[i] == '>' || data->line[i] == '<' || data->line[i] == '|') {
            new_len += 3; // " > " or " < " or " | " plus spaces
            i++;
        } else {
            new_len++; // Regular character
            i++;
        }
    }
    
    // Allocate memory for the new string
    char *new_line = malloc(new_len + 1);
    if (!new_line)
        return NULL;
    
    i = 0;
    while (i < len) {
        if (data->line[i] == ' ') {
            while (data->line[i] == ' ')
                i++;
        }

        if ((data->line[i] == '>' && data->line[i + 1] == '>') ||
            (data->line[i] == '<' && data->line[i + 1] == '<')) {
            new_line[j++] = ' ';
            new_line[j++] = data->line[i++];
            new_line[j++] = data->line[i++];
            new_line[j++] = ' ';
        } else if (data->line[i] == '>' || data->line[i] == '<' || data->line[i] == '|') {
            new_line[j++] = ' ';
            new_line[j++] = data->line[i++];
            new_line[j++] = ' ';
        } else {
            new_line[j++] = data->line[i++];
        }
    }
    
    new_line[j] = '\0'; // Null-terminate the new string
    
    return new_line;
}

// int main() {
//     t_data data;
//     data.line = "   some  >     text<and >>more <<|text|";
    
//     char *modified_line = add_spaces(&data);
//     if (modified_line) {
//         printf("Original: '%s'\n", data.line);
//         printf("Modified: '%s'\n", modified_line);
//         free(modified_line);
//     }
    
//     return 0;
// }
