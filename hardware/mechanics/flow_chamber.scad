// ******Flow Through colorimeter Nano Castro, Pablo Cremades****//

$fn=30;
// Parametros del cubo de medición
cube_h=24; 
cube_w=24;
cube_l=25;

// Parámetros TCS34725
tcspcb_w=0.8*25.4;
tcspcb_l=0.8*25.4;
tcspcb_depth=3;
tcspcb_led_h=1.4;
sensorloc_w=0.39;//ubicación del sensor en ancho pcb
sensorloc_l=0.41;//ubicación del sensor en alto pcb
sensor_w=2;
sensor_l=2.4;

// Parámetros del OPT101
//sensor_w=6.12;
//sensor_l=9.34;
//sensor_depth=1.45;
// Parametros de photodiodo
//photo_w=2.2;

// Parametros del tubo
tube_diam=4.5+0.1;//corregido 0.1
// Parametros del LED
led_diam=5;
led_l=7;
// Parametro haz de luz
light_diam=1+0.3;//corregido 0.3

difference(){
cube([cube_l,cube_w,cube_h],center=true);

/// Para OPT101
//translate([0,cube_w/2-sensor_depth/2,0])
//cube([sensor_l,sensor_depth,sensor_w],center=true);//abertura para sensor
//translate([0,cube_w/2-tube_diam/2,0])
//cube([photo_w,tube_diam,photo_w],center=true);

translate([-tcspcb_w/2,cube_w/2-tcspcb_depth,-tcspcb_l/2])
cube([tcspcb_w,tcspcb_depth,tcspcb_l]);

rotate([0,90,0])
translate([0,tube_diam/2,-0.1])
#cylinder(r=tube_diam/2,h=3*cube_w,center=true);//abertura para paso del tubo de fluido
     
translate([-0.1,-cube_w/2+led_l/2,-0.1])
rotate([90,0,0])
    cylinder(r=led_diam/2,h=led_l,center=true);//abertura para led
rotate([-90,0,0])
cylinder(d=sensor_l,h=cube_w/2);
translate([-0.1,0,-0.1])
rotate([90,0,0]) 
#cylinder(r=light_diam/2,h=1.5*cube_w,center=true);

//arreglo para imprimir....
translate([0,cube_w/5,0])
rotate([30,0,0])
translate([-cube_w/2-2,-cube_w,-cube_l/2-2])
rotate([0,90,0])
cylinder(cube_l+2,cube_l,cube_l,$fn=4);

mirror([0,0,1])
translate([0,cube_w/5,0])
rotate([30,0,0])
translate([-cube_w/2-2,-cube_w,-cube_l/2-2])
rotate([0,90,0])
cylinder(cube_l+2,cube_l,cube_l,$fn=4);

}

