# ansible関連のTips

### ansibleをコマンドで実行する
```bash
cd /vagrant
ansible-playbook -D -l training_dev -i deploy/hosts/all.yml deploy/all.yml
```
