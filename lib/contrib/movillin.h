!-------------------------------------------------------------------
! movillin.h
!
! Clase que permite el movimiento lineal en una sola dirección
!
!            baltasarq@yahoo.es
!-------------------------------------------------------------------

Constant dir_NORTE  10;
Constant dir_SUR    11;
Constant dir_ESTE   12;
Constant dir_OESTE  13;
Constant dir_ARRIBA 14;
Constant dir_ABAJO  15;

Message "Compilando módulo de movimientos lineales v030828";
System_file;

class MovilLineal
private
    ruta dir_NORTE,
    sitio nothing,
    activo false,
    loc_meta nothing,
    loc_anterior nothing,
    turnosPorLocalidad 0,
    turnosEsperando 0,
with
    arrancarMovil [dir meta;
        self.loc_anterior = nothing;
        self.sitio        = parent(self);
        self.loc_meta     = meta;
        self.ruta         = dir;
        self.turnosEsperando = 0;
        ArrancarDaemon(self);
    ],
    getSitioAnterior [;
        return self.loc_anterior;
    ],
    despuesDeParar [;
        rtrue;
    ],
    antesDeMoverse [;
        if (self.getSitioActual() == localizacion)
        {
            print (el) self, " se va hacia ";
            print self.dirACadena(), ".";
        }
        rtrue;
    ],
    despuesDeMoverse [;
        rtrue;
    ],
    pararMovil [;
        PararDaemon(self);
        self.activo = false;
        return self.despuesDeParar();
    ],
    getSitioActual [;
        return self.sitio;
    ],
    getRuta [;
        return self.ruta;
    ],
    getActivo [;
        return self.activo;
    ],
    getMeta [;
        return self.loc_meta;
    ],
    daemon [;
        if (~~self.activo) {
             self.activo     = true;
             rtrue;
        }

        if (self.turnosEsperando > 0)
        {
            self.turnosEsperando--;
            rtrue;
        }
        
        self.loc_anterior = self.getSitioActual();

        if (self.antesDeMoverse())
        {
          if (self.moverse())
          {
             if (self.getSitioActual() == self.getMeta())
             {
                self.pararMovil();
             }
        
             self.turnosEsperando = self.turnosPorLocalidad;
          } else self.pararMovil();
    
          return self.despuesDeMoverse();
        } 
    ],
    moverse [lugar_dest toret;

        toret      = true;
        lugar_dest = nothing;

        if (self.ruta == dir_NORTE)
        {
            if (self.getSitioActual() provides al_n)
                lugar_dest = self.getSitioActual().al_n;
        } else
        if (self.ruta == dir_SUR)
        {
            if (self.getSitioActual() provides al_s)
                lugar_dest = self.getSitioActual().al_s;
        } else
        if (self.ruta == dir_ESTE)
        {
            if (self.getSitioActual() provides al_e)
                lugar_dest = self.getSitioActual().al_e;
        } else
        if (self.ruta == dir_OESTE)
        {
            if (self.getSitioActual() provides al_o)
                lugar_dest = self.getSitioActual().al_o;
        } else
        if (self.ruta == dir_ARRIBA)
        {
            if (self.getSitioActual() provides arriba)
                lugar_dest = self.getSitioActual().arriba;
        } else
        if (self.ruta == dir_ABAJO)
        {
            if (self.getSitioActual() provides abajo)
                lugar_dest = self.getSitioActual().abajo;
        }

        if (lugar_dest == nothing)
        {
            toret = false;
        }
        else {
            move self to lugar_dest;
            self.sitio = lugar_dest;
        }
        
        return toret;
    ],
    dirACadena [toret;
        switch (self.ruta) {
            dir_NORTE:  toret = "el norte";
            dir_SUR:    toret = "el sur";
            dir_ESTE:   toret = "el este";
            dir_OESTE:  toret = "el oeste";
            dir_ARRIBA: toret = "arriba";
            dir_ABAJO:  toret = "abajo";
        }
        return toret;
    ]
;