#!/bin/sh
printf "#!/bin/sh\nD=\`mktemp\`;sed '1,2d' \$0|zcat>\$D;chmod +x \$D;\$D;rm \$D;exit\n" >> $1_pack
gzip -c $1 >> $1_pack
