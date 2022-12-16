from collections import defaultdict


class Die:
    """
    Encapsulates die mechanics.
    """

    def __init__(self) -> None:
        """
        We let the number 1 face up in the beginning
        Ref: Orientation follows that of the unfolded die in the README.
        """
        self.top_face: str = 'T'
        self.left_face: str = 'L'
        self.right_face: str = 'R'
        self.forward_face: str = 'F'
        self.backward_face: str = 'B'
        self.downward_face: str = 'D'
        self.die_face_numbers: defaultdict[str, int] = defaultdict(int)

    def top_face_has_number(self) -> bool:
        """
        Returns true if there is a number assigned to the top face.
        """
        return self.die_face_numbers[self.top_face] != 0

    def get_top_face_number(self) -> None:
        """
        Returns the number associated with a die-face.
        """
        return self.die_face_numbers[self.top_face]

    def set_top_face_number(self, number: str) -> None:
        """
        Assigns a number to the index.
        """
        self.die_face_numbers[self.top_face] = number

    def tip_up(self) -> None:
        """
        Die moves to the square upwards.
        """
        previous_top_face = self.top_face
        previous_forward_face = self.forward_face
        previous_backward_face = self.backward_face
        previous_downward_face = self.downward_face

        self.top_face = previous_backward_face
        self.forward_face = previous_top_face
        self.backward_face = previous_downward_face
        self.downward_face = previous_forward_face

    def tip_down(self) -> None:
        """
        Die moves to the square downwards, which is equivalent
        to 3 tips-up.
        """
        for _ in range(3):
            self.tip_up()

    def tip_left(self) -> None:
        """
        Die moves to the square to the left
        """
        previous_top_face = self.top_face
        previous_left_face = self.left_face
        previous_right_face = self.right_face
        previous_downward_face = self.downward_face

        self.top_face = previous_right_face
        self.left_face = previous_top_face
        self.right_face = previous_downward_face
        self.downward_face = previous_left_face

    def tip_right(self) -> None:
        """
        Die moves to the square to the right, which is equivalent 
        to 3 tips-left.
        """
        for _ in range(3):
            self.tip_left()

    def serialize(self) -> str:
        return ''.join((
            self.top_face,
            self.left_face,
            self.right_face,
            self.forward_face,
            self.backward_face,
            self.downward_face))
