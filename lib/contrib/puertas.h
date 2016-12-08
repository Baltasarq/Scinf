! Libreria para simplificar la programación de puertas bidireccionales
! Version INFSP - 20061012

Class 	Conexion
 with  	direcc1 0,
        lado1 0,
      	direcc2 0,
        lado2 0,
      	door_dir [;
	    if (location==self.lado1) return self.direcc2;
	    return self.direcc1;
	],
	door_to [;
	    if (location==self.lado1) return self.lado2;
	    return self.lado1;
	],
	found_in [;
	    if (location==self.lado1 or self.lado2) rtrue;
	],
 has 	door openable static;

[ InicializarConexiones i j p;
    objectloop (i ofclass Habitacion) 
	objectloop (j in compass) 
	    if (i provides j.door_dir) 
	    {
		p=i.(j.door_dir);
		if (p ofclass Conexion) 
		{
		    if (p.direcc2==0) {
			p.direcc2=j.door_dir;
			p.lado1=i; 
		    }
		    else if (p.direcc1==0){
			p.direcc1=j.door_dir;
			p.lado2=i;
		    }
		    else print "[***Error de programación: puerta '",
			(name) p, "' conecta tres o más
			habitaciones***]^"; 
		}
	    }
    objectloop (i ofclass Conexion) {
	if ((i.direcc1==0)&&(i.direcc2==0))
	    print "[***Error de programación: puerta '", (name) i, "' no
		conecta habitaciones***]^";
	else if ((i.direcc1==0)||(i.direcc2==0)) {
	    print "[***Error de programación: la puerta '", (name) i,
		"' lleva sólo en una dirección (entrando desde ";
	    if (i.direcc1==0) print (name) i.lado1;
	    else print (name) i.lado2;
	    print ").***]^";
	}
    }
];

   
	 
    

	   
