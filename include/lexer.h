typedef struct s_segment t_segment;
typedef struct s_token t_token;

enum Quote
{
	NONE,
	SINGLE,
	DOUBLE,
};

enum Type
{
	WORD,
	PIPE,
	REDIRECT_IN,
	REDIRECT_OUT,
	HEREDOC,
	APPEND,
};

struct s_segment
{
	char		*text;
	enum Quote	quote;
};

struct s_token
{
	t_segment	**lexeme;
	enum Type	type;
};

t_token	**lexer(char *line);
