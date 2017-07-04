Fwlan0 :: FromDevice(wlan9);
Twlan0 :: ToDevice(wlan9);
kc :: KernelCtrl(IFACE wlan9);

Fwlan0 -> c1 :: Classifier(0/ff 2/ff 4/ff 14/6464, 14/6564, 14/6664 ,- );



c1[0] ->wl :: WL4ExpiryPeriod(EP 5);
wl[0] -> c2 :: Classifier(6/18d6 8/c7b8 10/e3f4 14/6464, 14/6564, 14/6664 ,- );
c2[0] -> Print("wlan9")-> kc;


c1[1] -> Discard;
wl[1] -> Discard;
kc[0] -> Discard;
kc[1] -> Print("to next")-> Queue(100) -> Twlan0;

c2[1] -> Discard;
c2[2] -> Discard;
c2[3] -> Discard;

c1[2] -> Discard;
c1[3] -> Discard;

