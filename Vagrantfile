# -*- mode: ruby -*-
# vi: set ft=ruby :

# coding: utf-8
VAGRANTFILE_API_VERSION = "2"

# 任意の場所で失敗させた時にエラーメッセージ出すために定義
def fail_with_message(msg)
  fail Vagrant::Errors::VagrantError.new, msg
end
# vagrant up時にプラグインを自動でインストールしたい場合に使用する。
def install_plugin(plugin)
  system "vagrant plugin install #{plugin}" unless Vagrant.has_plugin? plugin
end

# Windowsの場合はvboxfs使う可能性があるので、共有用ソフトを新しくするプラグインが入っているか確認する
if Vagrant::Util::Platform.windows? and !Vagrant.has_plugin? 'vagrant-vbguest'
  install_plugin "vagrant-vbguest"
end

# VMのディスク容量を設定できるようにするプラグイン
if !Vagrant.has_plugin? 'vagrant-disksize'
  install_plugin "vagrant-disksize"
end
if Vagrant.has_plugin?('vagrant-hostmanager')
  install_plugin "vagrant-hostmanager"
end

Vagrant.configure("2") do |config|
  config.vm.box = "centos/7"
  config.disksize.size = '50GB'
  config.vm.boot_timeout = 600

  config.vm.hostname = "vm.training.cs.test"
  config.hostmanager.enabled = true
  # 以下の行を追加すると、ホストOSのhostsへも追加してくれる。
  config.hostmanager.manage_host = true
  # 以下の行を追加すると、ゲストOSのhostsへも追加してくれる。
  config.hostmanager.manage_guest = true

  config.vm.synced_folder ".", "/vagrant", type: "virtualbox"

  # 構築に必要なリソース
  # VirtualboxのGUI上で見える名前など設定
  config.vm.provider "virtualbox" do |v|
    v.memory = 2048
    v.cpus = 2
    v.name = "infra_training"
  end
  # WSL移行してhyper-v化したら有効化
  #if Vagrant::Util::Platform.windows?
  #  config.vm.provider “hyperv” do |h|
  #    h.enable_virtualization_extensions = true
  #    h.differencing_disk = true
  #  end
  # hyper-v用意（hyper-vではprivate networkが使えないので。）
  # config.vm.provider “hyperv”
  # config.vm.network “public_network”
  #end
  # SSHやHTTPで接続確認のためにプライベートネットワークが必要
  config.vm.network "private_network", ip: "192.168.254.41"

  config.vm.provision "ansible_local", run: "always" do |ansible|
    ansible.limit = "training_dev"
    ansible.inventory_path = "./deploy/hosts/all.yml"
    ansible.playbook = "./deploy/all.yml"
  end
end
