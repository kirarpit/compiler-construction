#!/bin/bash

diff <(tr -d " \n" <.a.out) <(tr -d " \n" <.b.out);
