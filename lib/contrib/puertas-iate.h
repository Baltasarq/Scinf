! Libreria para simplificar la programación de puertas bidireccionales
!

Class 	Conexion
 with  	direcc1 0,
        lado1 0,
      	direcc2 0,
        lado2 0,
      	direcc_puerta [;
	    if (localizacion==self.lado1) return self.direcc2;
	    return self.direcc1;
	],
	puerta_a [;
	    if (localizacion==self.lado1) return self.lado2;
	    return self.lado1;
	],
	esta_en [;
	    if (localizacion==self.lado1 or self.lado2) rtrue;
	],
 has 	puerta abrible estatico;

[ InicializarConexiones i j p;
    objectloop (i ofclass Habitacion) 
	objectloop (j in brujula) 
	    if (i provides j.direcc_puerta) 
	    {
		p=i.(j.direcc_puerta);
		if (p ofclass Conexion) 
		{
		    if (p.direcc2==0) {
			p.direcc2=j.direcc_puerta;
			p.lado1=i; 
		    }
		    else if (p.direcc1==0){
			p.direcc1=j.direcc_puerta;
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

   
	 
    

	   
