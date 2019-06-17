void
grid2(Monitor *m ) {
	grid_in_generall(m,2);
}


void
grid_in_generall(const Monitor *m, unsigned int a) {
	/* First Bit is the bit of direction in which the gridlayout will put windows with not the same
	 * with unequal dimensions
	 * + + +
	 * + + +
	 * this is the first possibility
	 * + +
	 * + +
	 * + + 
	 * this is the second one 
	 *
	 * the second value is the one of how windows will be ordered, preferably in rows or in cols
	 *
	 * 1 2 3
	 * 4 5 6
	 * 7 8 9
	 *
	 * this is how they will be ordered in rows
	 *
	 * 1 4 7
	 * 2 5 8
	 * 3 6 9
	 *
	 * this is how they are ordered in columns
	 *
	 * Adding random text maybe it will compile now
	 */
	unsigned int d = a & 1;
	unsigned int e = a & (1 <<1);	
	

	unsigned int i,n,cx,cy,cw,ch,aw,ah,cols,rows;
	unsigned int swap;
	Client *c;
	for ( n = 0, c = nexttiled(m->clients);c;c= nexttiled(c->next))
		n++;
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n) break;
	cols = (rows && (rows -1 ) * rows >= n ) ? rows -1 :rows;

	if (!d){
		swap = cols;
		cols = rows;
		rows = swap;
	
	}
	ch = m->wh /(rows ? rows :1 );
	cw = m->ww /(cols ? cols :1 );
	for (i = 0 , c = nexttiled (m->clients ); c; c=nexttiled(c->next)) {
		if (e) {
			cy = m->wy + (i /cols ) * ch;
			cx = m->wx + ( i% cols ) *cw;
		/* adjust height/width of last row/columns's windows */
			aw = (( i+1 ) % cols == 0) ? m->ww -cw *cols :0;
			ah = ( i >= cols * ( rows -1 )) ? m->wh -ch *rows :0;


		}
		else {
			cx= m->wx + ( i / rows ) *cw;
			cy= m->wy + ( i % rows ) *ch;
			ah = (( i+1 ) % rows == 0) ? m->wh - ch *rows :0;
			aw = ( i >= rows * (cols -1 )) ? m->ww -cw *cols :0;
		}
		resize(c, cx, cy, cw - 2 * c->bw + aw, ch - 2 * c->bw + ah, False);
		i++;




	}	
}



void
grid_in_generall_enhanced(const Monitor *m, unsigned int a) {
	/* First Bit is the bit of direction in which the gridlayout will put windows with not the same
	 * with unequal dimensions
	 * + + +
	 * + + +
	 * this is the first possibility
	 * + +
	 * + +
	 * + + 
	 * this is the second one 
	 *
	 * the second value is the one of how windows will be ordered, preferably in rows or in cols
	 *
	 * 1 2 3
	 * 4 5 6
	 * 7 8 9
	 *
	 * this is how they will be ordered in coloums
	 *
	 * 1 4 7
	 * 2 5 8
	 * 3 6 9
	 *
	 * this is how they are ordered in rows
	 *
	 * Adding random text maybe it will compile now
	 */
	unsigned int d = a & 1;
	unsigned int e = a & (1 <<1);	
	unsigned int f = a & (1 <<2);
	unsigned int g = a & (1 <<3); 

	unsigned int diff,wuff=0,mycols,myrows;
	unsigned int i,n,cx,cy,cw,ch,aw,ah,cols,rows;
	unsigned int swap;
	Client *c;
	for ( n = 0, c = nexttiled(m->clients);c;c= nexttiled(c->next))
		n++;
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n) break;
	cols = (rows && (rows -1 ) * rows >= n ) ? rows -1 :rows;

	diff=cols*rows-n; /* number of rectangles - used ones */

	
	if (!d){
		swap = cols;
		cols = rows;
		rows = swap;
	
	}
	ch = m->wh /(rows ? rows :1 );
	cw = m->ww /(cols ? cols :1 );
	for (i = 0 , c = nexttiled (m->clients ); c; c=nexttiled(c->next)) {
		if (e) {
				cy = m->wy + (i /cols ) * ch;
				cx = m->wx + ( i% cols ) *cw;
		/* adjust height/width of last row/columns's windows */
				aw = (( i+1 ) % cols == 0) ? m->ww -cw *cols :0;
				ah = ( i >= cols * ( rows -1 )) ? m->wh -ch *rows :0;


		}
		else {
			cx= m->wx + ( i / rows ) *cw;
			cy= m->wy + ( i % rows ) *ch;
			ah = (( i+1 ) % rows == 0) ? m->wh - ch *rows :0;
			aw = ( i >= rows * (cols -1 )) ? m->ww -cw *cols :0;
			resize(c, cx, cy, cw - 2 * c->bw + aw, ch - 2 * c->bw + ah, False);
		}
		i++;




	}	
}
typedef struct que que;
 struct que {
	int pos;
	int width;
	que *next;

};


que* create_queue(){

       que *new= calloc(1, sizeof(que));
       return new;
}

que *add_queue(int pos,int width,que *z){

	que *new = create_queue();
	if (z){
	z->next=new;
	new->width=width;
	new->pos=pos;
	new->next=NULL;
	return z;
	} else{
		que *new = create_queue();
		new->width=width;
		new->pos=pos;
		new->next=NULL;
	}
	return new;
}
que *next_que (que *z) {
	if (z) {
	que *next=z->next;
	free(z);
	return next;
	}
	return z;

}

void
super_grid(const Monitor *m , unsigned int a) {
unsigned int width, height;
unsigned int cols,rows, cx,cy,cw,ch,i,j,swap,diff,wuff,mycols,myrows,n;
Client *c;
que *z=NULL;
	for (n=0;c=nexttiled(m->clients),c;c=nexttiled(c->next)) n++;
	
	for(rows = 0; rows <= n/2; rows++)
		if(rows*rows >= n) break;
	cols = (rows && (rows -1 ) * rows >= n ) ? rows -1 :rows;

	diff=cols*rows-n; /* number of rectangles - used ones */

	
		swap = cols;
		cols = rows;
		rows = swap;
	ch = m->wh /(rows ? rows :1 );
	cw = m->ww /(cols ? cols :1 );
	for (i=0;c=nexttiled(m->clients),c;c=nexttiled(c->next)) {
		if(diff>0) {
			mycols=0;
			myrows=0;
			while((mycols+1)*(myrows+1)<diff+1){
				swap=mycols;
				mycols=myrows;
				myrows=swap;
				mycols++;
			}
			for(j=0;j<myrows;j++){
				z= add_queue(i+j*myrows ,mycols,z);
			}
			width=mycols*(cw+1);
			height=myrows*(ch+1);
			diff-=(mycols+1)*(myrows+1)-1;
		}
		else {
			height=ch;
			width=cw;
		}
		cx=m->wx + (i %cols) *cw;
		cy=m->wy + (i /cols) *ch;
		if(z && z->pos==i){
		i+=z->width;
		z=next_que(z);
			resize(c,cx,cy,width-2*c->bw,  height - 2*c->bw, False );		
		}else {
		i++;
			resize(c, cx, cy,  width- 2 * c->bw ,  height- 2 * c->bw , False);
			/* 
			 * c->bw is the marginal thats why it makes perfectly sense to include it here. REEEEEEEE 
			 */
		}	
	}
}


void sgrid(Monitor *m){
	super_grid(m, 0);
}
