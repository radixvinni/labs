<?php
$p=floatval($_REQUEST['p']);

header ("Content-type: image/png");
$im = imagecreatetruecolor(320, 240);
imagealphablending( $im, false );
imagesavealpha( $im, true );

$bg = ImageColorAllocateAlpha($im, 255, 255, 255, 127); // (PHP 4 >= 4.3.2, PHP 5)
ImageFill($im, 0, 0 , $bg);

$ink = imagecolorallocate($im, 255, 216, 132);
imagefilledellipse($im,160,120,200,150,$ink);
$ink = imagecolorallocate($im, 224, 144, 0);
imagefilledarc($im,160,120,200,150,0,360*$p,$ink,IMG_ARC_PIE);

$ink = imagecolorallocate($im, 255, 255, 255);
//
imagestring($im, 5, 160, 120, strval(intval($p*100))."%", $ink);

imagepng($im);
imagedestroy($im);
?>