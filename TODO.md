- Make dynamic number of leds
- Add dynamic effect. See FastLED for timestamp
    ```python
    while True:
        command = tcp_listen()
    
        sleep(FPS)
    
        if command=='sinelon':
            if last_command=command:
                leds.sinelon(time_base=get_milis())
            leds.sinelon() # It internaly call get_milis().
        elif command=='fade slow'
            leds.fade_slow() # It internaly call get_milis().
    
        leds.set_matrix()
    
    ```
    - Some dynamics effects, take into account current level of leds, instead of time.
- Read commands from TCP
