void sighandler(int* signum) {
    finish = true;
}

volatile bool finish;

int main() {
    finish = flase;
    
    while(!finish) {
        do();
    }

==>
mov $rax, &finish
jump_not_equal $raw, 0
call_do_something
으로 컴파일 하는데 

volatile있으면 1~3 중에서 1라인이 없어짐

+. c와 java에서 volatile은 달라!
c : 항상 메모리에서 데이터를 가져와서 사용해라
java : 이 변수에 대해서 reordering을 하지마라 #memory berrier

int a = 42;

int main() {
    int b=42;

    a++; // a = a + 1
    finish = 40; // 어. 읽어올 필요가 없어서 이걸 먼저하고 a++ 하고 b =을 하자.
    b= b* a; //라는 옵티마이제이션을 finish 기준으로 순서 ㅂ꾸기 놉

    인데 finish가 volatile이면
    1~3라인을 컴파일러가 순서를 바꾸지 않는다.
} 

암튼 병렬 프로그래밍하는데 필요.

...haepen's before relation...?

}

점프로 무슨 잌셉션 ㅎㄹㄹ 중이심..

'

try (
    func() // may raise exception
) catch ( e) {

}