#include <stdio.h>
#include <stddef.h>
    typedef struct pointdatatype{
        int a,b;
    }point;

    typedef struct circledatatype{
        int radius;
        struct pointdatatype centre;
    }circle;
    
    int main(){
        int choice=0;
        printf("Enter 1 for part 2 OR Enter 2 for part 3\n");
        scanf("%d",&choice);
        if(choice==1){
            struct pointdatatype p;
            printf("Input a point\n");
            printf("X-coordinate:");
            scanf("%d", &p.a);
            printf("Y-coordinate:");
            scanf("%d", &p.b);
            printf("Input point is : P(%d,%d)\n",p.a, p.b);
            struct circledatatype c;
            printf("Input the details of circle:\n");
            printf("X-coordinate of center :");
            scanf("%d", &c.centre.a);
            printf("Y-coordinate of center:");
            scanf("%d", &c.centre.b);
            printf("Radius: ");
            scanf("%d", &c.radius);

            printf("Input Circle is: C[P[(%d,%d),%d]\n",c.centre.a, c.centre.b, c.radius);
            
            float dist;
            int x,y;//to store difference in x and y coordinates respectively
            x=p.a-c.centre.a;
            y=p.b-c.centre.b;
            dist=(x*x)+(y*y); //now stores the square of distance
            int radiussq = (c.radius)*(c.radius);
            if(dist>radiussq){
                printf("Relation of point with circle is: Point lies outside the circle.\n");
            }else if(dist==radiussq){
                printf("Relation of point with circle is: Point lies on the circle.\n");

            }else{
                printf("Relation of point with circle is: Point lies inside the circle.\n");
            }
            return 0;

        }
        else if(choice==2){
            struct circledatatype c1,c2;
            printf("Input the details of circle C1:\n");
            printf("X-coordinate of center :");
            scanf("%d", &c1.centre.a);
            printf("Y-coordinate of center:");
            scanf("%d", &c1.centre.b);
            printf("Radius: ");
            scanf("%d", &c1.radius);
            
            printf("Input the details of circle C2:\n");
            printf("X-coordinate of center :");
            scanf("%d", &c2.centre.a);
            printf("Y-coordinate of center:");
            scanf("%d", &c2.centre.b);
            printf("Radius: ");
            scanf("%d", &c2.radius);
            printf("Input Circle C2 is: C[P[(%d,%d),%d]",c2.centre.a, c2.centre.b, c2.radius);

            //Distance Between Centres
            float distance;
            int x,y;//to store difference in x and y coordinates respectively
            x=c2.centre.a-c1.centre.a;
            y=c2.centre.b-c1.centre.b;
            distance=(x*x)+(y*y); //now stores the square of distance bw wo radius
            int radsum = c1.radius+c2.radius;
            radsum=radsum*radsum;//square of radsum
            if(distance<radsum){
                printf("The relation between two circles is: C1 and C2 intersect\n");
            }else if(distance==radsum){
                printf("The relation between two circles is: C1 and C2 touch\n");
            }else{
                printf("The relation between two circles is: C1 and C2 are disjoint\n");
            }

        }else{
            printf("Invalid Choice");
        }
    }
