# https://github.com/catalyst-system-inc/cs_docker_apache_php
FROM catalystsystem/cs_docker_apache_php:2.4.39-7.3.14

# apacheのコマンドすぐ使いたいかもしれないからdir移動
WORKDIR /usr/local/httpd/bin

# ログを標準出力へ出すようにする
RUN mkdir -p /var/log/httpd/ \
    && touch /var/log/httpd/access.log \
    && touch /var/log/httpd/error.log \
    && ln -sf /dev/stdout /var/log/httpd/access.log \
    && ln -sf /dev/stdout /var/log/httpd/error.log

##############################################################################
# conf類は変わる可能性が高いから最後に書くこと！！
##############################################################################
# httpd-vhostsの設置
ADD httpd-vhosts.conf /usr/local/httpd/conf/extra/httpd-vhosts.conf
# php設定ファイル設置
ADD php.ini /usr/local/lib/php.ini
# 実行時にコマンド実行
ADD run /usr/local/bin/run

RUN chmod +x /usr/local/bin/run

# Dockerコンテナの指定したポートを開き他から参照できるようにします。
EXPOSE 80 443

ENTRYPOINT ["/usr/local/bin/run"]
