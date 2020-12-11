#2020 11 23

RREQ modified.

update "src" routingtable entry when receive RREQ


#2020 11 25

RREPACK modified.

something wrong in  'RecvRequest' , cuz it ignore all packets with same origin and Packet ID.
 Which means that AODV just process the first RREQ and build reverse route, but the shortest one. 


#2020 11 26

RREQ modified.

each time receive a RREQ, we will update metric first, than choose a better route.
 At last, check if it's duplicated packet.

 But sometimes,  when the "old nexthop" equels to src, the metric of old nexthop is 0. I dont know why, 
  but it seems make a very limited difference cuz each RREQ will be broadcast few times, expect the first time, metric works normally.



#2020 12 9

RREQ should not update so frequently, the first one usually means the best one.
