#!/bin/bash

#SCENARIO1=$(echo <<END
#Hello pouet "hello pouet" 'hello pouet'
#"Hello $USER 'pouet $USER'"
#'Hello $USER "pouet $USER"'
#Hello << >> < > pouet
#Hello<<<>>><>pouet
#"Hello < pouet"
#Hello | pouet
#"Hello | pouet"
#Hi"Hello pouet"Hi
#$USERi $USER/test test$USER
#h"hello"i "pouet'hi'" 'pouet' '"hi"'
#echo a > $USER
#echo $LS_COLORS
#unset LS_COLORS
#echo $?
#echo $LS_COLORS
#echo $TERM
#echo $COLORTERM
#echo $HOME
#unset TERM COLORTERM HOME
#echo $?
#echo $TERM
#echo $COLORTERM
#echo $HOME
#unset m4rd3
#echo $?
#unset pouet
#echo $?
#unset 666
#echo $?
#unset m4rd3 666 GNOME_DESKTOP_SESSION
#echo $?
#unset 0ups
#echo $?
#unset oldpwd
#echo $?
#echo $OLDPWD
#unset ...yey
#echo $?
#END)
#
#bash << ${SCENARIO1} >/tmp/bash-out.txt 2>&1  
#BASH_RC=$?
#./minishell << ${SCENARIO1} >/tmp/ms-out.txt 2>&1  
#MS_RC=$?
#
#diff /tmp/bash-out.txt /tmp/ms-out/txt
#
#
#./minishell <<EOF
#EOF

test_exit()
{
	#$1 : premier argument de la commande ou de la fonction de la chaine passee en parmetre
	VAL="$1"
	echo "=== Testing exit '$VAL' ==="
	echo ">> BASH <<"
	#2>&1 redirection de stderr vers stdout le >& siginfie que l arg de gauche est agrege dans
	#celui de droite
	bash <<<"exit ${VAL}" 2>&1
	EXPECT="$?"
	echo $EXPECT
	echo ">> MINISHELL <<"
	# <<< extension bash qui permet d envoyer une chaine en input de la commande
	./minishell <<<"exit ${VAL}"
	# -eq : VOIR MAN TEST (test est un builtin pour faire des conditions complexes
	#dans un script)
	if [ ! "$?" -eq "$EXPECT" ]; then
		echo "exit '${VAL}' FAILED (Wrong exit code: '${EXPECT}')." 2>&1
	else
		echo "exit '${VAL}' SUCCEEDED (Exit code ok: '${EXPECT}')." 2>&1
	fi
}
test_exit +42
test_exit 255
test_exit -42
test_exit ++++++++42
test_exit --------42
test_exit 123a
test_exit "a 1 2"
test_exit "1 2 3"
test_exit "\"1 2 3\""
test_exit 123456789123456789123
test_exit 9223372036854775808