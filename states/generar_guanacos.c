#include <stdio.h>
#include <time.h>

int main(){
	FILE *fp;
	int r, x, y, max;
	srand(time(NULL));
	max = 500000;
	fp = fopen ("0_guanacos.xml", "w+");
	fprintf(fp, "%s\n", "<agents>");
	while(max > 0){
		fprintf(fp, "%s\n", "<xagent>");
		fprintf(fp, "%s\n", "<name>manada_guanacos</name>");
		r = rand()%3;
		x = (rand()%14)+1;
		y = rand()%15;
		if(r > 0){
			fprintf(fp, "%s\n", "<familia>1</familia>");
			fprintf(fp, "%s\n", "<count>19</count>");
			fprintf(fp, "%s\n", "<adultos>10</adultos>");
			max -= 19;
		}else{
			fprintf(fp, "%s\n", "<familia>0</familia>");
			fprintf(fp, "%s\n", "<count>50</count>");
			fprintf(fp, "%s\n", "<adultos>50</adultos>");
			max -= 50;
		}
		fprintf(fp, "%s%d%s\n", "<x>", x, "</x>");
		fprintf(fp, "%s%d%s\n", "<y>", y, "</y>");
		fprintf(fp, "%s%d%s\n", "<targetX>", x, "</targetX>");
		fprintf(fp, "%s%d%s\n", "<targetY>", y, "</targetY>");
		fprintf(fp, "%s\n", "<calorias>0</calorias>");
		fprintf(fp, "%s\n", "<season>0</season>");
		fprintf(fp, "%s\n", "</xagent>");
	}

	fprintf(fp, "%s\n", "</agents>");
	fclose(fp);
}