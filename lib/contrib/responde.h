! responde.h
! -----------------------------------------------------------------------------
! Estas clases son vectores de mensajes: ellas solitas se encargan de escoger uno de
! los posibles.
! Véase pruresp.inf para más detalles.
! (c) Baltasar el arquero baltasarelarquero@yahoo.es
! Es necesario el módulo array.h
! Este código es freeware.
! -----------------------------------------------------------------------------
System_file;

IFNDEF RESPONDE_H;
Constant RESPONDE_H;

Include "Array";
Message "Compilando módulo de mensajes - respuesta v010924";

! -----------------------------------------------------------------------------
! Clase base
! -----------------------------------------------------------------------------

class respondona
class vector
private
	num 0
with
	reset [; self.num = 0;],
	dev_msg [; self.haz_accion(); return self.elemento(0); ],
	haz_accion [; return; ]
;

! -----------------------------------------------------------------------------
! Responde secuencialmente / al azar una serie de mensajes
! -----------------------------------------------------------------------------
class responde
class respondona
private
	hecho false,
with
	dev_msg [ n num_turns;
		#Ifdef VersionIdioma;
			num_turns = turnos;
		#Ifnot;
			num_turns = turns;
		#Endif;
		self.haz_accion();
		if ((num_turns % 3) == 0)
		{
			self.num = random(self.longitud() - 1);
			return self.elemento(self.num);
		}
		else {
			n = self.num;
			self.num++;
			if (n == self.longitud())
			{
				n = 0;
				self.num = 1;
			}
			return self.elemento(n);
		}
	]
;

! -----------------------------------------------------------------------------
! Responde con una serie de mensajes. No vuelve al principio, 
! siempre repite el último
! -----------------------------------------------------------------------------

class respondeUnaVez
class respondona
with
	haz_accion_final [; return; ],
	dev_msg [n;
		if (self.num == self.longitud())
            {
			self.haz_accion_final();
			return self.elemento(self.num - 1);
		}
		else {
			n = self.num;
			self.num++;
			self.haz_accion();
			return self.elemento(n);
		}
	]
;

ENDIF;