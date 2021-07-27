sudo mount -o loop ./hd.img ./hdisk/
sudo cp build/HelloOS.eki hdisk/boot/
sync
sudo umount ./hdisk/
cp hd.img /mnt/hgfs/from_vm/HelloOS/
