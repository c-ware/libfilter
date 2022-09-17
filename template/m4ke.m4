# M4ke

dnl Convert all files of a certain file extension
dnl in a directory to another extension.
dnl
dnl $1 the directory
dnl $2 the input file extension
dnl $2 the output file extension
define(`CONVERT_FILES', `syscmd(find $1 -type f | grep "\$2\$" | sed "s/\$2\$/$3/g" | tr "\\n" " ")')

dnl Declare a new implicit rule that will be expanded for
dnl each input and output extension. The input file should
dnl be expected as $1, and the output file $2
dnl
dnl $1 the input file extension
dnl $2 the output file extension
dnl $3 the body to expand
define(`NEW_IMPLICIT_RULE', `
	define(translit(IMPLICIT_RULE$1$2, ., _), `$3')
')

dnl Create a new rule with the filename, the input suffix,
dnl an output suffix. Uses the implicit macro rule defined
dnl with the file extensions
dnl
dnl $1 the name of the file, without extensions
dnl $2 the input extension
dnl $3 the output extension
dnl $4 extra dependencies
define(`NEW_RULE', `$1$3: $1$2 $4
translit(IMPLICIT_RULE$2$3, ., _)($1$2, $1$3)')
