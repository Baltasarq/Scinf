System_file;

CompassDirection estribor_obj "estribor" compass
with 
    name 'estribor' 'e//',
    door_dir e_to
;

CompassDirection babor_obj "babor" compass
with 
    name 'babor' 'b//',
    door_dir w_to
;

CompassDirection proa_obj "proa" compass
with 
    name 'proa',
    door_dir n_to
;

CompassDirection popa_obj "popa" compass
with 
    name 'popa',
    door_dir s_to
;

[ eliminarTodasLasConexiones x y;
	x = child( compass );
	while( x ~= Nothing ) {
		y = sibling( x );
		move x to limbo;
		x = y;
	}
];

[ moverConexionesNauticas obj;
    move popa_obj to obj;
    move proa_obj to obj;
    move babor_obj to obj;
    move estribor_obj to obj;
];

[ moverBrujula obj;
	move n_obj to obj;
	move s_obj to obj;
	move e_obj to obj;
	move w_obj to obj;
];

[ pasar_a_ConexionesNauticas;
	eliminarTodasLasConexiones();

	! Mover todo lo de la nave a la brújula del sistema
	moverConexionesNauticas( compass );
];

[ pasar_a_Brujula;
	eliminarTodasLasConexiones();

	! Mover todo lo de la brújula a la brújula del sistema
	moverBrujula( compass );
];
