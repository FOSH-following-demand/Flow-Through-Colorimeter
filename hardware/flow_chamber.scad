// ******Flow Through colorimeter Nano Castro, Pablo Cremades****//

$fn=30;
// Parametros del cubo de medición
cube_h=10; 
cube_w=20;
cube_l=20;
// Parámetros del OPT101
sensor_w=6.12;
sensor_l=9.34;
sensor_depth=1.45;
// Parametros de photodiodo
photo_w=2.2;
// Parametros del tubo
tube_diam=6.10;
// Parametros del LED
led_diam=5;
led_l=7;
// Parametro haz de luz
light_diam=1;

difference(){

cube([cube_l,cube_w,cube_h],center=true);

translate([0,cube_w/2-sensor_depth/2,0])
cube([sensor_l,sensor_depth,sensor_w],center=true);//abertura para sensor
rotate([0,90,0])
translate([0,tube_diam/2,0])
    cylinder(r=tube_diam/2,h=2*cube_l,center=true);//abertura para paso del tubo de fluido
 
translate([0,cube_w/2-tube_diam/2,0])
    cube([photo_w,tube_diam,photo_w],center=true);
translate([0,-cube_w/2+led_l/2,0])
rotate([90,0,0])
    cylinder(r=led_diam/2,h=led_l,center=true);//abertura para led
rotate([90,0,0]) 
#cylinder(r=light_diam/2,h=1.5*cube_w,center=true);
}