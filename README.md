
# sizewrite

read/write blobs of data directly to block devices

## usage

    $ sizewrite secrets.tar.gpg /dev/sda
  
    $ sizeread /dev/sda secrets.tar.gpg

## how it works

It writes a single 64-bit integer followed by the data
