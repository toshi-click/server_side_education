### (必須) 仮想化ソフトの導入
`Vitualbox`と`Vagrant`を下記リンクよりダウンロードしインストールしてください
- [Virtualbox](https://www.virtualbox.org/)
- [Vagrant](https://www.vagrantup.com/downloads.html)

### 下記コマンドもしくはIDEのプラグインでVagrantを操作することができます。
#### Vagrant起動
```
cd [プロジェクトをクローンしたディレクトリ]
# このコマンドでVM起動および自動で環境構築開始！
vagrant up
```

## Vagrantの終了
```
cd [プロジェクトをクローンしたディレクトリ]
# このコマンドでVM終了！
vagrant halt
```

## Vagrantの再起動
```
cd [プロジェクトをクローンしたディレクトリ]
# このコマンドでVM再起動
vagrant reload
```

## Vagrantで上げたVMにアクセスする
```
cd [プロジェクトをクローンしたディレクトリ]
# windowsはsshクライアントをコマンドプロンプトに追加していない場合は接続情報が表示されるのでsshクライアントでアクセスしてください
vagrant ssh

# VMに入れてrootユーザになりたい場合(vagrantユーザにはsudo no passwordついてます)
sudo su -
```

## 参考：vagrantがエラーになった場合の対応

Vagrant boxのcentosが最新ではないため、yum updateする必要があります。

```sh
vagrant ssh
sudo su -
yum update
```
