# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure("2") do |config|
  # Use the latest Ubuntu LTS as the base box (22.04 Jammy Jellyfish)
  config.vm.box = "ubuntu/jammy64"

  # Define a single virtual machine
  config.vm.define "cmake_env" do |cmake_env|
    cmake_env.vm.hostname = "cmake-env"
    
    # Allocate resources
    cmake_env.vm.provider "virtualbox" do |vb|
      vb.memory = "2048"
      vb.cpus = 2
    end

    # Provisioning script to install gcc, cmake, and ctest
    cmake_env.vm.provision "shell", inline: <<-SHELL
      echo "Updating package repositories..."
      apt-get update
      
      echo "Installing build-essential (includes gcc)..."
      apt-get install -y build-essential
      
      echo "Installing the latest cmake (which includes ctest)..."
      apt-get install -y cmake
      
      # Verify installations
      echo "Installed versions:"
      gcc --version
      cmake --version
      ctest --version
    SHELL
  end
end