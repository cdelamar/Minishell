**FONCTIONNEMENT DU PARSING** 🔄:

Le parsing prend un char **
- Ajout des nodes
  - : `add_node(token_list, argc, argv, i)`
- Lexer (metre tout dans une liste chainee et metre des enum sur les nodes)
  - : `lexer(t_token *token, int argc, char **argv)`
  - dans le lexer assigner les enum `assign_enum(token, index)`
