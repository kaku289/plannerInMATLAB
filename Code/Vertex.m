classdef Vertex
   properties
       id = 0;
       x = 0;
       y = 0;
   end
   methods
       function V = Vertex(id,x,y)
           if nargin == 3
               V.id = id;
               V.x = x;
               V.y = y;
           end
       end
       function TF = eq(V1, V2)
           if V1.id == V2.id
               TF = true;
           else
               TF = false;
           end
       end
   end
end