touch  $1
echo '<scene>' > $1
ls | awk '/.*.3d/{print "<model file=\"" $0 "\" />"}' >> $1
echo '</scene>' >> $1
