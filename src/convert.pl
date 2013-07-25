
$dir='./';
$fileExt='xy';
$is=",";
$willBe= '.';
opendir (DH,$dir) or die "Can't access directory\n";

while ($olditem = $item = readdir DH) {
       if ($item !~ /\.$fileExt$/) {
               print "Skipping $item\n";
               next;
               }
       $olditem =~ s/\.$fileExt$/.bak/;
       rename "$dir/$item","$dir/$olditem";
       open (FHI,"$dir/$olditem");
       open (FHO,">$dir/$item");
       read(FHI,$buffer,-s "$dir/$olditem");
       $count = ($buffer =~ s/$is/$willBe/g);
       print (($count+0)." changes to file $item\n");
       print FHO $buffer;
       }


